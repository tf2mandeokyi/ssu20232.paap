const { readdir } = require('fs/promises');


/**
 * @param {string} source 
 * @returns { Promise<string[]> }
 */
const getDirectories = async source => (await readdir(source, { withFileTypes: true }))
        .filter(entry => entry.isDirectory())
        .map(entry => entry.name);


/**
 * @param {string} root
 * @returns { Promise<{ [x: string]: string }> }
 */
const getDirectoryMap = async root => (await getDirectories(root))
        .map(entry => ({ num: entry.slice(0, entry.indexOf('-')), directory: entry }))
        .filter(({ num, _ }) => !Number.isNaN(parseInt(num)))
        .reduce((prev, { num, directory }) => { prev[num] = directory; return prev }, {})


module.exports = { getDirectories, getDirectoryMap }