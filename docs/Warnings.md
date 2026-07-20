# Docme Warning Codes

Docme warnings are represented by `docme::core::Warning::Code` in
`docme/core/warnings.mpp`. Package-specific warning types derive from
`docme::core::Warning` and own their package message table in a `warnings`
component:

| Package | Warning Type | Message Table |
| --- | --- | --- |
| Core | `docme::core::Warning` | `docme/core/warnings.mpp` |
| Config | `docme::config::Warning` | `docme/config/warnings.mpp` |
| App | `docme::app::Warning` | `docme/app/warnings.mpp` |
| Generator | `docme::generator::Warning` | `docme/generator/warnings.mpp` |
| CLI | `docme::cli::Warning` | `docme/cli/warnings.mpp` |

Runtime messages are built as:

```text
(DOCME_W<code>) <message body>
```

The special `DOCME_WARNING` code formats as `ANONYMOUS` instead of a numeric
code. Warnings are buffered through `docme::core::Warning::propagate()` and can
be pulled from the warning buffer by call site.

## Code Groups

| Range | Group | Source | Status |
| --- | --- | --- | --- |
| `DOCME_W100-199` | Core | `docme::core` | Declared, no warning messages currently registered |
| `DOCME_W200-299` | Config | `docme::config`, `docme::app` | Active |
| `DOCME_W300-399` | App | `docme::app`, `docme::cli` | Active |
| `DOCME_W400-499` | Generator | `docme::generator` | Active |
| `DOCME_W500-599` | CLI | `docme::cli` | Active |
| `DOCME_W600-699` | GUI | `docme::gui` | Reserved |
| `DOCME_W700-799` | Plugin | `docme::plugin` | Reserved |
| `DOCME_WARNING` | Misc | `docme::core` | Active |

## Core Warnings

`DOCME_W100` is declared in `docme::core::Warning::Code`, but
`docme::core::Warning` currently has no registered warning messages.

## Config Warnings

| Code | Warning Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_W200` | `docme::config::Warning` | `Unkown entry with the key "{key}" in config file "{path}"` | A config file contains a key that Docme does not recognize. | Remove the key or correct its spelling if it was intended to be a supported config option. |

## App Warnings

| Code | Warning Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_W201` | `docme::app::Warning` | `Creating the confile file "{path}" when a config file already exists at "{current default config path}"` | The `init` command is creating an explicitly requested config file while the default config file already exists. | Confirm the second config file is intentional, or use the existing default config. |

`{current default config path}` is built from
`std_fs::current_path() / config::File::DEFAULT_CONFIG_FILE`.

## CLI Warnings

| Code | Warning Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_W300` | `docme::cli::Warning` | `Command line arguments parsed with warnings` | The CLI parser completed, but one or more warnings were produced. | Inspect the warnings that were propagated while parsing arguments. |
| `DOCME_W500` | `docme::cli::Warning` | `Positional arguments provided but aren't being used` | A `--config` option was provided, so positional config arguments are ignored. | Remove the positional argument or omit `--config` if the positional config path should be used. |
| `DOCME_W501` | `docme::cli::Warning` | `Too many positional arguments provided` | More than one positional argument was provided where at most one config path is used. | Keep only the intended config path. Extra positional arguments are ignored. |

## Generator Warnings

| Code | Warning Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_W400` | `docme::generator::Warning` | `Encountered file system error while trying to access "{path}"` | A file system operation failed while generator code was checking a path. | Confirm the path exists, permissions allow access, and the file system is available. |
| `DOCME_W401` | `docme::generator::Warning` | `Ignore file or path does not exist "{path}"` | A configured source or ignore path does not exist. | Correct the path or remove it from the configuration. |

## Misc Warnings

| Code | Warning Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_WARNING` | `docme::core::Warning` | `Unknown warning has occurred` | Anonymous fallback warning. The formatted code is `ANONYMOUS`. | Prefer propagating a specific package warning code where possible. |

## Reserved Groups

### GUI `DOCME_W600-699`

No GUI warning messages are currently registered.

### Plugin `DOCME_W700-799`

No plugin warning messages are currently registered.
