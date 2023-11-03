const { glob } = require('glob');
const { Zip } = require('zip-lib')
const path = require('path')
const { getProjectNumber, getDirectory, getConfig } = require('../utils/project')


/**
 * @param {string} root 
 * @param {import('minimist').ParsedArgs} args 
 */
module.exports = async function(root, args) {
    
    let projectNumber = getProjectNumber(args);
    let projectDir = await getDirectory(root, projectNumber);
    let projectConfig = getConfig(projectDir);

    let zipConfig = projectConfig?.zip;

    let zipExcludes = zipConfig?.exclude ?? []
    let files = await glob('**/*', { cwd: projectDir, ignore: [ ...zipExcludes, 'config.yml' ] })

    let zip = new Zip();
    let zipRenames = zipConfig?.rename ?? {};
    for(let file of files) {
        let source = path.join(projectDir, file);
        let dest = file in zipRenames ? zipRenames[file] : file;
        zip.addFile(source, dest);
    }

    let studentId = process.env['student_id']
    let destination = path.join(root, 'build', zipConfig?.name ?? `${studentId}_${projectNumber}.zip`)
    await zip.archive(destination);
}