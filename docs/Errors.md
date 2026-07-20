# Docme Error Codes

Docme errors are represented by `docme::core::Error::Code` in
`docme/core/errors.mpp`. Package-specific error types derive from
`docme::core::Error` and own their package message table in an `errors`
component:

| Package | Error Type | Message Table |
| --- | --- | --- |
| Core | `docme::core::Error` | `docme/core/errors.mpp` |
| Config | `docme::config::Error` | `docme/config/errors.mpp` |
| App | `docme::app::Error` | `docme/app/errors.mpp` |
| Generator | `docme::generator::Error` | `docme/generator/errors.mpp` |
| CLI | `docme::cli::Error` | `docme/cli/errors.mpp` |

Runtime messages are built as:

```text
(DOCME_E<code>) <message body>
```

The special `DOCME_ERROR` and `DOCME_INTERNAL` codes format as
`ANONYMOUS` and `INTERNAL` instead of numeric codes.

## Code Groups

| Range | Group | Source | Status |
| --- | --- | --- | --- |
| `DOCME_E100-199` | Core | `docme::core` | Active |
| `DOCME_E200-299` | Config | `docme::config` | Active |
| `DOCME_E300-399` | App | `docme::app` | Active |
| `DOCME_E400-499` | Generator | `docme::generator` | Active |
| `DOCME_E500-599` | CLI | `docme::cli` | Declared, no package error messages currently registered |
| `DOCME_E600-699` | GUI | `docme::gui` | Reserved |
| `DOCME_E700-799` | Plugin | `docme::plugin` | Reserved |
| `DOCME_ERROR`, `DOCME_INTERNAL` | Misc | `docme::core` | Active |

## Core Errors

| Code | Error Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_E100` | `docme::core::Error` | `Failed to load json file at {path}` | A JSON file could not be opened or failed while being read. | Confirm the file exists, the process can read it, and the path points to the intended JSON file. |
| `DOCME_E101` | `docme::core::Error` | `While parsing json could not find key {key}` | A required JSON key was missing from the parsed document. | Add the missing key to the JSON file. For config files, compare against `resources/templateConfigFile.json`. |
| `DOCME_E102` | `docme::core::Error` | `While parsing json expected string at {key} but got wrong type` | A JSON value was expected to be a string. This can also happen when a list exists, but one of its elements is not a string. | Change the value to a string. For string lists, make every array item a string. |
| `DOCME_E103` | `docme::core::Error` | `While parsing json expected list at {key} but got wrong type` | A JSON value was expected to be an array/list. | Change the value to a JSON array. If the array is meant to contain paths or names, make each item a string. |
| `DOCME_E104` | `docme::core::Error` | `Failed to parse json file at {path}` | A JSON file was opened, but its contents could not be parsed into a valid JSON document. | Validate the JSON syntax, including commas, quotes, braces, brackets, and trailing commas. |
| `DOCME_E105` | `docme::core::Error` | `Failed to load dynamic library "{name}" at path "{path}"` | A dynamic library could not be loaded. | Confirm the library file exists, is readable, has the expected binary format, and can be loaded by the current platform. |
| `DOCME_E106` | `docme::core::Error` | `Failed to get function "{function}" from dynamic library "{library}"` | A loaded dynamic library does not expose the requested function. | Confirm the plugin exports the expected function name and uses the expected ABI. |
| `DOCME_E107` | `docme::core::Error` | `Cannot get function "{function}" because dynamic library "{library}" is not loaded` | Code tried to resolve a function from a library that was not successfully loaded. | Load the library first and handle any prior `DOCME_E105` failure before requesting functions from it. |

## Config Errors

| Code | Error Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_E200` | `docme::config::Error` | `Could not locate template config file in "{path}"` | The built-in template config file could not be found when creating a new config file. | Confirm `resources/templateConfigFile.json` exists relative to the binary resources directory, and that resources were copied or packaged with the build. |
| `DOCME_E201` | `docme::config::Error` | `Could not create new template config file in "{path}"` | Docme could not create a new config file from the template. This can happen while checking the target path or copying the template file. | Confirm the destination directory exists, the process has write permission, and the path is valid. |
| `DOCME_E202` | `docme::config::Error` | `Given config file is not a .json file at "{path}"` | A config path was provided with an unsupported extension. | Use a `.json` config file path, or pass a directory so Docme can use the default `docme.json` name. |
| `DOCME_E203` | `docme::config::Error` | `Given config file already exists at "{path}"` | Docme tried to create a template config file, but a file already exists at the destination. | Choose a different output path, delete or move the existing file, or load the existing config instead of creating a new template. |
| `DOCME_E204` | `docme::config::Error` | `Failed to load config file at "{path}"` | The config file path could not be checked, opened, or parsed into a valid config file. | Confirm the file exists, is readable, has the `.json` extension, and contains the required config keys with the expected value types. |
| `DOCME_E205` | `docme::config::Error` | `Expected a strings from the key "{key}" in config file at "{path}" but got wrong type` | A config key was present but was not a string. | Change the config value to a string. This currently applies to string-valued config entries such as `projectName` and `output`. |
| `DOCME_E206` | `docme::config::Error` | `Expected a list of strings from the key "{key}" in config file at "{path}" but got wrong type` | A config key was present but was not a list of strings. | Change the config value to an array of strings. This currently applies to list-valued entries such as `source`, `ignore`, `languageHandlers`, and `renderers`. |

## App Errors

| Code | Error Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_E300` | `docme::app::Error` | `Failed to initialize the default config file as a default config file already exists at location "{current default config path}"` | The `init` command was asked to create the default config file, but one already exists in the current working directory. | Pass an explicit config path if a second config file is intentional, or use the existing default config file. |

`{current default config path}` is built from
`std_fs::current_path() / config::File::DEFAULT_CONFIG_FILE`.

## Generator Errors

| Code | Error Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_E400` | `docme::generator::Error` | `Invalid plugin type "{actual}" for "{handler}", expected "{expected}"` | A plugin registry entry exists, but its type does not match the expected language handler type. | Update the plugin registry metadata so the entry type matches the expected handler type. |
| `DOCME_E401` | `docme::generator::Error` | `Could not find language handler "{handler}" in plugin registry` | The requested language handler tag was not found in the plugin registry. | Add the language handler to the plugin registry or correct the configured handler tag. |
| `DOCME_E402` | `docme::generator::Error` | `Metadata path "{path}" for language handler "{handler}" does not exist or is not a file` | A language handler metadata path is missing or points to something other than a file. | Correct the metadata path in the plugin registry and confirm the file exists. |
| `DOCME_E403` | `docme::generator::Error` | `Metadata path "{path}" for language handler "{handler}" is not a "{extension}" file` | A language handler metadata path exists but does not use the expected metadata extension. | Use a metadata file with the expected extension. |
| `DOCME_E404` | `docme::generator::Error` | `Failed to parse metadata file "{path}" for language handler "{handler}"` | The metadata file could not be parsed as valid JSON. | Validate the metadata JSON syntax. |
| `DOCME_E405` | `docme::generator::Error` | `While parsing metadata file "{path}" for language handler "{handler}", field "{field}" is not of type "{type}"` | A required metadata field exists but has the wrong JSON type. | Change the metadata field to the expected type. |
| `DOCME_E406` | `docme::generator::Error` | `While parsing metadata file "{path}" for language handler "{handler}", could not find field "{field}"` | A required metadata field was missing. | Add the missing field to the language handler metadata file. |
| `DOCME_E407` | `docme::generator::Error` | `Failed to load library from "{path}" for language handler "{handler}"` | The language handler binary listed in metadata could not be loaded as a dynamic library. | Confirm the binary path is correct, the file exists, and the library is compatible with the current platform. |
| `DOCME_E408` | `docme::generator::Error` | `Failed to load function "{function}" from language handler "{handler}"` | A loaded language handler library does not expose a required function. | Confirm the plugin exports the required function and uses the expected ABI. |

## CLI Errors

`DOCME_E500` and `DOCME_E501` are declared in `docme::core::Error::Code`,
but `docme::cli::Error` currently has no registered package error messages.
The positional argument cases are currently emitted as warnings
`DOCME_W500` and `DOCME_W501`.

## Misc Errors

| Code | Error Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_ERROR` | `docme::core::Error` | `An unknown error has occurred` | Anonymous fallback error. The formatted code is `ANONYMOUS`. | Prefer returning a specific package error code where possible. |
| `DOCME_INTERNAL` | `docme::core::Error` | `An internal error has accord "{message}"` | Internal fallback error with a formatted context message. The formatted code is `INTERNAL`. | Treat this as an unexpected internal failure and inspect the wrapped message. |

## Reserved Groups

### GUI `DOCME_E600-699`

No GUI error messages are currently registered.

### Plugin `DOCME_E700-799`

No plugin error messages are currently registered.
