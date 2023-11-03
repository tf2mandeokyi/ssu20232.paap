const path = require('path');
const subcommands = require('./src/subcommands')
require('dotenv').config({ path: path.resolve(__dirname, '../.env') });

const root = path.resolve(__dirname, '..') // Since we're in build-src, we first get out of the __dirname


/**
 * The main function
 * @param {import('minimist').ParsedArgs} args
 */
async function main(args) {
    switch(args._[2]) {
        case 'help': {
            subcommands.help();
            break;
        }
        case 'run': {
            await subcommands.run(root, args);
            break;
        }
        case 'zip': {
            await subcommands.zip(root, args);
            break;
        }
    }
}


if(require.main === module) {
    if(process.env['student_id'] === undefined) {
        console.error('Student ID not provided in .env file in the project root folder');
        process.exit(-1);
    }

    let args = require('minimist')(process.argv);
    if(args._.length < 3) {
        console.error(`No sub command found; Try "./run.sh help" or "./run.bat help"`)
        process.exit(-1);
    }

    if(args['help'] || args['h']) {
        console.log('');
        console.log('command options:');
        console.log('   --project, -p [number]: sets project number to zip up');
        console.log('');
        return;
    }

    main(args);
}