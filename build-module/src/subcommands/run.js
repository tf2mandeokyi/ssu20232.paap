const { spawn } = require('child_process')
const commandExists = require('command-exists')
const { getDirectory, getProjectNumber, getProperties } = require('../utils/project')


/**
 * @param {string} projectDir 
 * @param {string} command
 * @param {string[]} args
 */
async function execute(projectDir, command, args) {
    let result = await new Promise((res, _) => {
        const child = spawn(command, args, {
            cwd: projectDir,
            detached: true,
            stdio: 'inherit'
        });
        child.on('exit', (code, _) => {
            res(code);
        })
    })
    return result;
}


/**
 * @param {string} root 
 * @param {import('minimist').ParsedArgs} args 
 */
module.exports = async function(root, args) {
    if(!(await commandExists('gcc'))) {
        console.error(`Command "gcc" not found on this environment`);
        process.exit(-1);
    }

    let projectNumber = getProjectNumber(args);
    let projectDir = await getDirectory(root, projectNumber);
    let projectProperties = getProperties(projectDir);

    let commands = projectProperties.run;
    if(commands === undefined) {
        console.error('The "run" property in "properties.yml" is not defined');
        process.exit(-1);
    }
    if(!Array.isArray(commands)) {
        console.error('The "run" property in "properties.yml" is not an array');
        process.exit(-1);
    }

    for(let { command, args } of commands) {
        console.log(`Executing command: ${command} ${(args ?? []).join(' ')}`)
        let exitCode = await execute(projectDir, command, args ?? []);
        if(exitCode != 0) {
            console.error(`Process "${command}" exited with non-zero exit code(${exitCode}) (args: ${args})`);
            console.error(`Aborting...`);
            process.exit(-1);
        }
    }
}