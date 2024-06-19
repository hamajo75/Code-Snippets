# Testing

## unittest
Build in `uninttest` module.

- **Test Cases** 
    - Subclasses of `unittest.TestCase`. 
- **Test Suites**
    - Collections of test cases or other test suites.
    - Grouped together for efficient execution or organization.
- **Test Fixtures**
    - Provide common setup and teardown operations for test cases.

Execution of tests:
    
    python -m unittest test_add.py

## MagicMock

The `unittest.mock` library in Python provides a powerful mechanism for creating mock objects during testing. One of the most versatile classes in this library is MagicMock, which can be used to mock objects in your tests