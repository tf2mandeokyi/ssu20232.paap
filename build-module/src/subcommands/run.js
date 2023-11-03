const { spawn } = require('child_process')
const commandExists = require('command-exists')
const { getDirectory, getProjectNumber, getConfig } = require('../utils/project')


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
    let projectConfig = getConfig(projectDir);
    if(projectConfig === undefined) {
        console.error('The file "config.yml" is not found in the project');
        process.exit(-1);
    }

    let commands = projectConfig.run;
    if(commands === undefined) {
        console.error('The "run" property in "config.yml" is not defined');
        process.exit(-1);
    }
    if(!Array.isArray(commands)) {
        console.error('The "run" property in "config.yml" is not an array');
        process.exit(-1);
    }

    let platform = process.platform
    for(let osDependantCommand of commands) {
        let { command, args } = osDependantCommand[platform] ?? osDependantCommand['default'];
        
        console.log(`Executing command: ${command} ${(args ?? []).join(' ')}`)
        let exitCode = await execute(projectDir, command, args ?? []);
        if(exitCode != 0) {
            console.error(`Process "${command}" exited with non-zero exit code(${exitCode}) (args: ${args})`);
            console.error(`Aborting...`);
            process.exit(-1);
        }
    }
}