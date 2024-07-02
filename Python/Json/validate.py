import jsonschema
from jsonschema import validate, FormatChecker
from jsonschema.exceptions import ValidationError

# Define the JSON schema
schema = {
    "type": "object",
    "properties": {
        "date": {
            "type": "string",
            "format": "date"
        }
    },
    "required": ["date"]
}

# JSON data to be validated
data = {
    "date": "2023-07-02"  # This should be in the format YYYY-MM-DD
}

# Validate the JSON data
try:
    validate(instance=data, schema=schema, format_checker=FormatChecker())
    print("Validation passed!")
except ValidationError as e:
    print("Validation error:", e.message)

# Example of invalid date data
invalid_data = {
    "date": "2023/07/02"  # Incorrect format
}

# Validate the invalid JSON data
try:
    validate(instance=invalid_data, schema=schema, format_checker=FormatChecker())
    print("Validation passed!")
except ValidationError as e:
    print("Validation error:", e.message)
