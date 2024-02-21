from setuptools import find_packages
from setuptools import setup

requires = [
    "python-qpid-proton>=0.37.0",
]

setup(
    name="basic_application",
    version="0.1.0",
    description='Short description of your application',
    long_description=open('README.md').read(),  # Include README if applicable
    url='https://github.com/your-username/your_app',  # Your project's URL
    author='Your Name',
    author_email='your_email@example.com',
    license='MIT',  # Or appropriate license
    packages=find_packages(),  # Locate packages automatically
    install_requires=requires,
    entry_points={  # Optional: Create command-line entry points
        'console_scripts': [
            'basic_application = basic_application.module:main'
        ]
    },
    test_suite='tests'  # Optional: Specify test suite location
)
