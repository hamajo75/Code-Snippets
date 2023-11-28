# Jenkins Build Server

- Jenkins uses a domain specific language based on Groovy.

## Groovy
- https://www.tutorialspoint.com/groovy/index.htm

## Some central Jenkins objects
- `stages` is map name -> `stage`

## Shared Libraries
- https://www.jenkins.io/doc/book/pipeline/shared-libraries/

Load external repositories into a pipeline.

### vars Folder
- `vars` directory holds script files that are exposed as a variable in
Pipelines (filename = variable name).

To use a library add this to Jenkinfile:

    library('my-shared-library@1.0')

### src Folder
- You can put actual classes here.
- Pass `this` pointer into any class that needs to use Jenkins objects
  - e.g. `sh()`, `docker`
  - `env` variable
- Log with `jenkins.echo()` where `jenkins` is the `this` pointer.