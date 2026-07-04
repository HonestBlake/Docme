# Reusable VS Code Task Setup

This guide explains how to reproduce the VS Code task system used in this
project. It focuses on `.vscode/tasks.json` and the PowerShell scripts called by
those tasks.

The exact task names, preset names, compiler versions, executable names, and
dependency names are project-specific. The reusable part is how tasks are
declared, connected, parameterized, and kept safe.

## 1. Task System Overview

The task system has three layers:

```text
Visible task
    -> optional hidden subtasks
        -> optional PowerShell script
```

- **Visible tasks** are actions a developer runs from VS Code.
- **Hidden tasks** are implementation steps used by a compound task.
- **PowerShell scripts** handle validation, branching, file operations, and
  executable paths.

The current task categories are:

| Task | Purpose |
|---|---|
| Reload Clangd | Run several indexing-related steps in sequence |
| Select Compiler | Ask for a compiler and save the selection |
| Clean Deps | Delete one approved dependency directory or all of them |
| Clean Build | Delete one approved build directory or all of them |
| Configure | Open an extension command from a task button |
| Clean Binaries | Invoke the active build system's clean operation |
| Build | Invoke the active build command |
| Launch | Ask which executable configuration to run |

## 2. Basic `tasks.json` Structure

VS Code task files use this outer structure:

```json
{
  "version": "2.0.0",
  "tasks": [],
  "inputs": []
}
```

- `tasks` contains the actions that VS Code can run.
- `inputs` contains prompts whose values can be passed to tasks.

A minimal shell task looks like this:

```json
{
  "label": "Example Task",
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-Command",
    "Write-Host 'Task executed'"
  ],
  "problemMatcher": []
}
```

The `label` is the task's identifier. Other tasks and debugger configurations
must reference it exactly.

## 3. User-Facing Tasks

A user-facing task should have:

- A clear `label`.
- A short `detail`.
- Predictable terminal presentation.
- A status-bar button when the status-bar task extension is being used.
- Either a direct command or a call to a script.

Example:

```json
{
  "label": "Clean Build",
  "options": {
    "statusbar": {
      "label": "Configure",
      "icon": {
        "id": "trash"
      },
      "hide": false
    }
  },
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-File",
    "${workspaceFolder}/.vscode/scripts/clean-build.ps1",
    "-Config",
    "${input:cleanBuildConfig}",
    "-WorkspaceRoot",
    "${workspaceFolder}"
  ],
  "problemMatcher": [],
  "presentation": {
    "reveal": "always",
    "panel": "dedicated",
    "clear": true
  },
  "detail": "Delete one approved build directory or all approved build directories."
}
```

The task remains small because validation and deletion are handled in the
script.

## 4. Status-Bar Task Buttons

This project uses the Tasks extension's `options.statusbar` property:

```json
{
  "options": {
    "statusbar": {
      "label": "Build",
      "icon": {
        "id": "settings-gear"
      },
      "hide": false
    }
  }
}
```

Fields:

- `label` is the short text shown in the status bar.
- `icon.id` is a VS Code Codicon name.
- `hide: false` makes the button visible.

Possible icons include:

```text
trash
play
debug-restart
settings-gear
symbol-reference
server-process
```

This feature requires:

```text
actboy168.tasks
```

If that extension is not desired, remove `options.statusbar`. The tasks will
still be available through **Tasks: Run Task**.

## 5. Task Inputs

Inputs let a task prompt the user before running:

```json
{
  "id": "cleanBuildConfig",
  "type": "pickString",
  "description": "Select the build directory to delete",
  "options": [
    "All",
    "Index",
    "Release",
    "Debug"
  ],
  "default": "All"
}
```

Use the input inside a task with:

```json
"${input:cleanBuildConfig}"
```

For example:

```json
{
  "args": [
    "-File",
    "${workspaceFolder}/.vscode/scripts/clean-build.ps1",
    "-Config",
    "${input:cleanBuildConfig}"
  ]
}
```

The input ID is an internal reference. The description and options are shown to
the user.

### Keep task inputs and scripts synchronized

If the task offers these values:

```json
{
  "options": [
    "All",
    "Debug",
    "Release"
  ]
}
```

The script should accept exactly those values:

```powershell
[ValidateSet("All", "Debug", "Release")]
[string]$Config
```

When adding or renaming an option, update both locations.

## 6. Calling PowerShell Scripts

Use `-File` when a task has more than a trivial command:

```json
{
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-File",
    "${workspaceFolder}/.vscode/scripts/example.ps1",
    "-WorkspaceRoot",
    "${workspaceFolder}"
  ]
}
```

The flags have specific purposes:

- `-NoProfile` prevents user profile code from changing task behavior.
- `-ExecutionPolicy Bypass` permits the project script for that invocation.
- `-File` runs a script without constructing a large inline command.
- `${workspaceFolder}` gives the script an explicit project root.

Keep scripts in:

```text
.vscode/scripts/
```

This makes the task implementation easy for a developer or AI to discover.

## 7. Compound Tasks and Hidden Steps

The clangd reload action is a compound task. It does not execute a command
itself; it coordinates several subtasks:

```json
{
  "label": "Reload Clangd",
  "dependsOrder": "sequence",
  "dependsOn": [
    "Clangd: Shutdown",
    "Configure Index Data",
    "Build Index Data",
    "Clangd: Restart"
  ],
  "problemMatcher": [],
  "detail": "Regenerate indexing data and restart clangd."
}
```

`dependsOrder: "sequence"` is important. Without it, VS Code may run the
dependency tasks in parallel.

The intended order is:

```text
shutdown
    -> configure
    -> build
    -> restart
```

Implementation tasks can be hidden:

```json
{
  "label": "Configure Index Data",
  "hide": true,
  "type": "cmake",
  "command": "configure",
  "preset": "Index",
  "problemMatcher": []
}
```

`hide: true` keeps internal steps out of the normal task picker while still
allowing `dependsOn` to run them.

### Failure behavior in compound tasks

VS Code stops a sequential dependency chain when one task fails.

For most task chains, this is correct. The clangd indexing chain is a special
case: configuration may produce useful editor data even if the following build
does not compile successfully. A wrapper script can report the failure but
return success so the restart step still runs:

```powershell
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [string]$WorkspaceRoot
)

$ErrorActionPreference = "Stop"
$workspace = [System.IO.Path]::GetFullPath($WorkspaceRoot)
$buildExitCode = 0

try {
    Push-Location -LiteralPath $workspace
    try {
        & cmake --build --preset Index
        $buildExitCode = if ($null -ne $LASTEXITCODE) {
            $LASTEXITCODE
        } elseif ($?) {
            0
        } else {
            1
        }
    } finally {
        Pop-Location
    }
} catch {
    $buildExitCode = 1
    Write-Warning "Index build failed: $($_.Exception.Message)"
}

if ($buildExitCode -ne 0) {
    Write-Warning "Index build exited with code $buildExitCode."
    Write-Warning "Continuing so the final restart task can run."
}

exit 0
```

Only use this pattern when continuing is intentional. A normal build task should
return its real failure code.

## 8. Running Extension Commands

VS Code commands can be expanded inside tasks:

```json
"${command:cmake.build}"
```

Example build task:

```json
{
  "label": "Build",
  "type": "process",
  "command": "${command:cmake.build}",
  "problemMatcher": [],
  "detail": "Build through the active build extension."
}
```

Example task that opens a preset picker:

```json
{
  "label": "Configure",
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-Command",
    "$null = '${command:cmake.selectConfigurePreset}'"
  ],
  "problemMatcher": [],
  "presentation": {
    "reveal": "never",
    "panel": "shared",
    "clear": false
  }
}
```

Example clangd implementation tasks:

```json
{
  "label": "Clangd: Shutdown",
  "hide": true,
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-Command",
    "$null = '${command:clangd.shutdown}'"
  ],
  "problemMatcher": []
}
```

```json
{
  "label": "Clangd: Restart",
  "hide": true,
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-Command",
    "$null = '${command:clangd.restart}'"
  ],
  "problemMatcher": []
}
```

These commands require the extensions that register them. If an extension is
missing, task command expansion will fail.

## 9. Safe Cleanup Tasks

Cleanup tasks are destructive, so the task should offer a fixed list and the
script should independently validate it.

Example task:

```json
{
  "label": "Clean Build",
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-File",
    "${workspaceFolder}/.vscode/scripts/clean-build.ps1",
    "-Config",
    "${input:cleanBuildConfig}",
    "-WorkspaceRoot",
    "${workspaceFolder}"
  ],
  "problemMatcher": []
}
```

Example safe cleanup script:

```powershell
[CmdletBinding(SupportsShouldProcess = $true)]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("All", "Index", "Release", "Debug")]
    [string]$Config,

    [Parameter(Mandatory = $true)]
    [string]$WorkspaceRoot
)

$ErrorActionPreference = "Stop"

$allowedTargets = @("Index", "Release", "Debug")
$targets = if ($Config -eq "All") {
    $allowedTargets
} else {
    @($Config)
}

$workspace = [System.IO.Path]::GetFullPath($WorkspaceRoot)
$buildRoot = [System.IO.Path]::GetFullPath(
    (Join-Path $workspace "build")
)
$buildRootPrefix = $buildRoot.TrimEnd(
    [System.IO.Path]::DirectorySeparatorChar,
    [System.IO.Path]::AltDirectorySeparatorChar
) + [System.IO.Path]::DirectorySeparatorChar

foreach ($target in $targets) {
    $targetPath = [System.IO.Path]::GetFullPath(
        (Join-Path $buildRoot $target)
    )

    if (-not $targetPath.StartsWith(
        $buildRootPrefix,
        [System.StringComparison]::OrdinalIgnoreCase
    )) {
        throw "Refusing to delete outside the build directory: $targetPath"
    }

    if ((Split-Path -Leaf $targetPath) -ne $target) {
        throw "Refusing to delete an unexpected path: $targetPath"
    }

    if (Test-Path -LiteralPath $targetPath -PathType Container) {
        if ($PSCmdlet.ShouldProcess($targetPath, "Delete build directory")) {
            Remove-Item -LiteralPath $targetPath -Recurse -Force
            Write-Host "Removed $targetPath"
        }
    } else {
        Write-Host "No directory found at $targetPath"
    }
}
```

This protects the deletion with:

1. A fixed `ValidateSet`.
2. Full path resolution.
3. A check that the target remains inside the allowed root.
4. A check that the final directory name matches the approved name.
5. `SupportsShouldProcess`, which enables testing with `-WhatIf`.

Test it before the first real deletion:

```powershell
powershell -File .vscode/scripts/clean-build.ps1 `
  -Config All `
  -WorkspaceRoot $PWD `
  -WhatIf
```

Use the same pattern for dependency cleanup. Change the root directory and
approved names, but retain all path checks.

## 10. Compiler Selection Task

The compiler task passes a selected label to a script:

```json
{
  "label": "Select Compiler",
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-File",
    "${workspaceFolder}/.vscode/scripts/select-compiler.ps1",
    "-Compiler",
    "${input:compiler}"
  ],
  "problemMatcher": []
}
```

Its input is a fixed list:

```json
{
  "id": "compiler",
  "type": "pickString",
  "description": "Select the compiler",
  "options": [
    "GCC",
    "Clang"
  ],
  "default": "GCC"
}
```

The script should map labels to paths instead of accepting an arbitrary command:

```powershell
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("GCC", "Clang")]
    [string]$Compiler
)

$ErrorActionPreference = "Stop"

$toolchains = @{
    "GCC" = @{
        CC = "C:\Toolchains\gcc\bin\gcc.exe"
        CXX = "C:\Toolchains\gcc\bin\g++.exe"
    }
    "Clang" = @{
        CC = "C:\Toolchains\llvm\bin\clang.exe"
        CXX = "C:\Toolchains\llvm\bin\clang++.exe"
    }
}

$selected = $toolchains[$Compiler]

foreach ($path in @($selected.CC, $selected.CXX)) {
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) {
        throw "Compiler path does not exist: $path"
    }
}

Write-Host "Selected compiler: $Compiler"
Write-Host "CC=$($selected.CC)"
Write-Host "CXX=$($selected.CXX)"

# Save the selected paths to the configuration file used by the project.
```

The task's responsibility is prompting and passing the choice. The script owns
path lookup, validation, and persistence.

## 11. Launch Task

A launch task prompts for a configuration and passes it to a script:

```json
{
  "label": "Launch",
  "type": "shell",
  "command": "powershell",
  "args": [
    "-NoProfile",
    "-ExecutionPolicy",
    "Bypass",
    "-File",
    "${workspaceFolder}/.vscode/scripts/launch-project.ps1",
    "-Config",
    "${input:launchTarget}",
    "-WorkspaceRoot",
    "${workspaceFolder}"
  ],
  "problemMatcher": [],
  "presentation": {
    "reveal": "always",
    "panel": "dedicated",
    "clear": true
  }
}
```

Input:

```json
{
  "id": "launchTarget",
  "type": "pickString",
  "description": "Select the executable to launch",
  "options": [
    "Debug",
    "Release"
  ],
  "default": "Debug"
}
```

Script:

```powershell
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet("Debug", "Release")]
    [string]$Config,

    [Parameter(Mandatory = $true)]
    [string]$WorkspaceRoot
)

$ErrorActionPreference = "Stop"

$workspace = [System.IO.Path]::GetFullPath($WorkspaceRoot)
$binRoot = [System.IO.Path]::GetFullPath((Join-Path $workspace "bin"))
$binRootPrefix = $binRoot.TrimEnd(
    [System.IO.Path]::DirectorySeparatorChar,
    [System.IO.Path]::AltDirectorySeparatorChar
) + [System.IO.Path]::DirectorySeparatorChar

$relativeTarget = switch ($Config) {
    "Debug" { "debug\my-project.exe" }
    "Release" { "my-project.exe" }
}

$targetPath = [System.IO.Path]::GetFullPath(
    (Join-Path $binRoot $relativeTarget)
)

if (-not $targetPath.StartsWith(
    $binRootPrefix,
    [System.StringComparison]::OrdinalIgnoreCase
)) {
    throw "Refusing to launch outside the binary directory: $targetPath"
}

if (-not (Test-Path -LiteralPath $targetPath -PathType Leaf)) {
    throw "Could not find executable: $targetPath"
}

Write-Host "Launching ${Config}: $targetPath"
& $targetPath

if ($null -ne $LASTEXITCODE -and $LASTEXITCODE -ne 0) {
    exit $LASTEXITCODE
}
```

The script should use a fixed configuration-to-path mapping. Do not construct an
executable path from unrestricted user input.

## 12. Terminal Presentation

The `presentation` object controls the task terminal:

```json
{
  "presentation": {
    "reveal": "always",
    "panel": "dedicated",
    "clear": true
  }
}
```

Useful values:

| Property | Value | Meaning |
|---|---|---|
| `reveal` | `always` | Show the terminal when the task runs |
| `reveal` | `never` | Keep the terminal hidden |
| `panel` | `dedicated` | Give the task its own terminal |
| `panel` | `shared` | Reuse a terminal with other tasks |
| `clear` | `true` | Clear old output before running |

Recommended behavior:

- Cleanup and launch tasks: `always`, `dedicated`, `clear`.
- Picker-only extension commands: `never`, `shared`.
- Compound task implementation steps: only configure presentation when their
  output is useful.

## 13. Problem Matchers

This project generally uses:

```json
{
  "problemMatcher": []
}
```

That means the task does not parse terminal output into VS Code diagnostics.

This is suitable when:

- An extension already reports diagnostics.
- The task only performs cleanup or launching.
- The script's plain terminal output is sufficient.

If a task directly invokes a compiler, linter, or test tool, use an appropriate
problem matcher so errors can appear in the Problems panel.

## 14. Recommended Complete Task Skeleton

This compact file demonstrates the reusable relationships:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Reload Indexer",
      "dependsOrder": "sequence",
      "dependsOn": [
        "Indexer: Shutdown",
        "Indexer: Configure",
        "Indexer: Build",
        "Indexer: Restart"
      ],
      "problemMatcher": []
    },
    {
      "label": "Indexer: Shutdown",
      "hide": true,
      "type": "shell",
      "command": "powershell",
      "args": [
        "-NoProfile",
        "-Command",
        "$null = '${command:clangd.shutdown}'"
      ],
      "problemMatcher": []
    },
    {
      "label": "Indexer: Configure",
      "hide": true,
      "type": "cmake",
      "command": "configure",
      "preset": "Index",
      "problemMatcher": []
    },
    {
      "label": "Indexer: Build",
      "hide": true,
      "type": "shell",
      "command": "powershell",
      "args": [
        "-NoProfile",
        "-ExecutionPolicy",
        "Bypass",
        "-File",
        "${workspaceFolder}/.vscode/scripts/build-index-continue.ps1",
        "-WorkspaceRoot",
        "${workspaceFolder}"
      ],
      "problemMatcher": []
    },
    {
      "label": "Indexer: Restart",
      "hide": true,
      "type": "shell",
      "command": "powershell",
      "args": [
        "-NoProfile",
        "-Command",
        "$null = '${command:clangd.restart}'"
      ],
      "problemMatcher": []
    },
    {
      "label": "Clean Build",
      "type": "shell",
      "command": "powershell",
      "args": [
        "-NoProfile",
        "-ExecutionPolicy",
        "Bypass",
        "-File",
        "${workspaceFolder}/.vscode/scripts/clean-build.ps1",
        "-Config",
        "${input:cleanBuildConfig}",
        "-WorkspaceRoot",
        "${workspaceFolder}"
      ],
      "problemMatcher": []
    },
    {
      "label": "Launch",
      "type": "shell",
      "command": "powershell",
      "args": [
        "-NoProfile",
        "-ExecutionPolicy",
        "Bypass",
        "-File",
        "${workspaceFolder}/.vscode/scripts/launch-project.ps1",
        "-Config",
        "${input:launchTarget}",
        "-WorkspaceRoot",
        "${workspaceFolder}"
      ],
      "problemMatcher": []
    }
  ],
  "inputs": [
    {
      "id": "cleanBuildConfig",
      "type": "pickString",
      "description": "Select the build directory to delete",
      "options": [
        "All",
        "Index",
        "Debug",
        "Release"
      ],
      "default": "All"
    },
    {
      "id": "launchTarget",
      "type": "pickString",
      "description": "Select the executable to launch",
      "options": [
        "Debug",
        "Release"
      ],
      "default": "Debug"
    }
  ]
}
```

## 15. Instructions for an AI Agent

When adapting this task system to another project, an AI should inspect the
existing task and script files before editing them.

It should discover:

```json
{
  "visibleTasks": [
    "build",
    "clean",
    "launch",
    "select compiler",
    "reload indexer"
  ],
  "taskInputs": {
    "buildConfigurations": [],
    "launchConfigurations": [],
    "compilerChoices": [],
    "cleanableDependencies": []
  },
  "externalCommands": [],
  "scriptDirectory": ".vscode/scripts",
  "executableMappings": {},
  "destructiveTaskRoots": []
}
```

This is an information model for the AI, not a required file.

The AI should preserve these rules:

1. Keep visible task labels short and stable.
2. Keep implementation-only tasks hidden.
3. Use `dependsOrder: "sequence"` when order matters.
4. Reference task labels exactly in `dependsOn` and `preLaunchTask`.
5. Use task inputs for small, fixed choices.
6. Keep input options synchronized with script `ValidateSet` values.
7. Put complex behavior in scripts instead of inline command strings.
8. Pass `${workspaceFolder}` instead of assuming the terminal's current
   directory.
9. Validate all destructive paths after resolving them to full paths.
10. Keep cleanup targets restricted to a fixed allowlist.
11. Keep launch targets restricted to a fixed configuration-to-path mapping.
12. Return real failure codes unless a documented compound workflow must
    continue.
13. Preserve unrelated tasks, inputs, settings, and scripts.
14. Do not rename a task without updating every reference to its label.
15. Do not assume an extension command exists without identifying the extension
    that provides it.

## 16. Verification Checklist

After creating or modifying the tasks:

1. Parse `tasks.json` as JSON.
2. Confirm every `${input:name}` has a matching input ID.
3. Confirm every `dependsOn` label exists.
4. Confirm every script path exists.
5. Confirm task argument names match script parameter names.
6. Confirm input options match script `ValidateSet` values.
7. Parse each PowerShell script for syntax errors.
8. Run cleanup scripts with `-WhatIf`.
9. Test each compound task and confirm its steps run in order.
10. Test expected failure behavior for each compound step.
11. Confirm status-bar buttons appear if the Tasks extension is used.
12. Confirm extension command tasks work with a newly opened VS Code window.
13. Confirm launch tasks reject missing or unapproved executable paths.

## 17. Common Task Errors

- **Input prompt does not appear:** the task does not reference the input with
  `${input:id}`, or the ID is misspelled.
- **Compound steps run together:** `dependsOrder: "sequence"` is missing.
- **Compound task stops too early:** an intermediate task returned a failure
  code.
- **A hidden task appears in the picker:** `hide: true` is missing.
- **Script receives the wrong value:** task input options and `ValidateSet` are
  out of sync.
- **Script cannot be found:** use
  `${workspaceFolder}/.vscode/scripts/script-name.ps1`.
- **Extension command is unresolved:** the extension that registers the command
  is not installed or enabled.
- **Status-bar button is missing:** the status-bar Tasks extension is not
  installed, or `options.statusbar.hide` is true.
- **Old terminal output is confusing:** use a dedicated panel with
  `clear: true`.
- **Cleanup can target an unsafe path:** add an allowlist, full-path
  normalization, root containment checking, and final-name checking.

## 18. Porting Summary

To reuse this task system in another project:

1. Copy the desired task definitions.
2. Copy or recreate their scripts.
3. Replace project-specific task inputs and labels.
4. Replace compiler, dependency, preset, and executable mappings.
5. Keep hidden implementation tasks behind simple visible tasks.
6. Keep all destructive operations guarded by script validation.
7. Verify all labels, input IDs, arguments, and script parameters as one
   connected system.

The central pattern is simple:

```text
tasks.json describes what the user can do
inputs constrain what the user can select
hidden tasks coordinate ordered steps
scripts safely implement non-trivial behavior
```
