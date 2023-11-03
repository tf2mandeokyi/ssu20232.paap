/**
 * @param {string} str
 * @param {string} delimiter
 * @return {string}
 */
const trimMargin = function(str, delimiter='|') {
    return str.split('\n')
        .filter(line => line.includes(delimiter))
        .map(line => line.slice(line.indexOf(delimiter) + 1))
        .join('\n')
}


module.exports = function() {
    console.log(trimMargin(`
       |
       |usage:
       |    node build-module/index.js <subcommand> [options]
       |    ./run.sh <subcommand> [options]
       |    ./run.bat <subcommand> [options]
       |
       |subcommands:
       |    help: prints this message
       |    run: runs the project specified with an option --project (or -p)
       |    zip: zips the project specified with an option --project (or -p) to the build directory
       |
       |options:
       |    --project, -p <number>:
       |        specifies the project with the provided number
       |
    `));
}