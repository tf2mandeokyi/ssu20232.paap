const fs = require('fs');
const YAML = require('yaml')
const path = require('path');
const { getDirectoryMap } = require('./directory');


/**
 * @param {string} projectRoot
 * @param {string} propertiesFile
 * @returns {import('./interface').ProjectProperties}
 */
function getProperties(projectRoot, propertiesFile='properties.yml') {
    let fileDirectory = path.join(projectRoot, propertiesFile)
    try {
        let file = fs.readFileSync(fileDirectory, 'utf-8');
        return YAML.parse(file)
    } catch(e) {
        console.error(`File "${propertiesFile}" not found on the project`);
        process.exit(-1);
    }
}


/**
 * @param {import('minimist').ParsedArgs} args
 * @returns {number}
 */
function getProjectNumber(args) {
    let projectNumber = args['project'] ?? args['p'];
    if(typeof projectNumber === 'undefined') {
        console.error('No project number specifed. specify it with --project <number>');
        process.exit(-1);
    }
    if(typeof projectNumber !== 'number') {
        console.error('Invalid argument for project number');
        process.exit(-1);
    }
    return projectNumber;
}


/**
 * @param {string} root
 * @param {number} number
 */
async function getDirectory(root, projectNumber) {

    const directoryMap = await getDirectoryMap(root);

    let projectName = directoryMap[projectNumber];
    if(typeof projectName === 'undefined') {
        console.error(`Project with number ${projectNumber} doesn't exist`);
        process.exit(-1);
    }

    return path.join(root, projectName);
}


module.exports = { getProperties, getProjectNumber, getDirectory }