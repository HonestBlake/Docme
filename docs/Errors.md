# Docme Error Codes

Docme errors are represented by `docme::core::Error::Code` in
`docme/core/errors.mpp`. Runtime messages are built as:

```text
(DOCME_<code>) <message body>
```

The message body is defined by the error type that derives from
`docme::core::Error`.

## Code Groups

| Range | Group | Source | Status |
| --- | --- | --- | --- |
| `DOCME_100-199` | Core | `docme::core` | Active |
| `DOCME_200-299` | Engine | `docme::engine` | Active |
| `DOCME_300-399` | Generator | `docme::generator` | Reserved |
| `DOCME_400-499` | CLI | `docme::cli` | Reserved |

## Core Errors

Core errors currently come from `docme::core::Json::Error`.

| Code | Error Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_100` | `docme::core::Json::Error` | `Failed to load json file at {path}` | A JSON file could not be opened or failed while being read. | Confirm the file exists, the process can read it, and the path points to the intended JSON file. |
| `DOCME_101` | `docme::core::Json::Error` | `While parsing json could not find key {key}` | A required JSON key was missing from the parsed document. | Add the missing key to the JSON file. For config files, compare against `resources/templateConfigFile.json`. |
| `DOCME_102` | `docme::core::Json::Error` | `While parsing json expected string at {key} but got wrong type` | A JSON value was expected to be a string. This can also happen when a list exists, but one of its elements is not a string. | Change the value to a string. For string lists, make every array item a string. |
| `DOCME_103` | `docme::core::Json::Error` | `While parsing json expected list at {key} but got wrong type` | A JSON value was expected to be an array/list. | Change the value to a JSON array. If the array is meant to contain paths or names, make each item a string. |
| `DOCME_104` | `docme::core::Json::Error` | `Failed to parse json file at {path}` | A JSON file was opened, but its contents could not be parsed into a valid JSON document. | Validate the JSON syntax, including commas, quotes, braces, brackets, and trailing commas. |

## Engine Errors

Engine errors currently come from `docme::engine::ConfigFile::Error`.

| Code | Error Type | Message Body | Description | Relevant Fix |
| --- | --- | --- | --- | --- |
| `DOCME_200` | `docme::engine::ConfigFile::Error` | `Could not locate template config file in {path}` | The built-in template config file could not be found when creating a new config file. | Confirm `resources/templateConfigFile.json` exists relative to the binary resources directory, and that resources were copied or packaged with the build. |
| `DOCME_201` | `docme::engine::ConfigFile::Error` | `Could not create new template config file in {path}` | Docme could not create a new config file from the template. This can happen while checking the target path or copying the template file. | Confirm the destination directory exists, the process has write permission, and the path is valid. |
| `DOCME_202` | `docme::engine::ConfigFile::Error` | `Given config file is not a .json file at {path}` | A config path was provided with an unsupported extension. | Use a `.json` config file path, or pass a directory so Docme can use the default `docme.json` name. |
| `DOCME_203` | `docme::engine::ConfigFile::Error` | `Given config file already exists at {path}` | Docme tried to create a template config file, but a file already exists at the destination. | Choose a different output path, delete or move the existing file, or load the existing config instead of creating a new template. |
| `DOCME_204` | `docme::engine::ConfigFile::Error` | `Failed to load config file at {path}` | The config file path could not be checked, opened, or parsed into a valid config file. | Confirm the file exists, is readable, has the `.json` extension, and contains the required config keys with the expected value types. |

## Reserved Groups

### Generator `DOCME_300-399`

No generator error codes are currently defined.

### CLI `DOCME_400-499`

No CLI error codes are currently defined.
