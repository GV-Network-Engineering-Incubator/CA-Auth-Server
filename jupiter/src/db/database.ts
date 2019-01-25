import Knex from 'knex';
import get from 'lodash/get';
import config from './knexfile';
import getNodeEnv from '../helpers/get-node-env';

const env = getNodeEnv();
let envConfig = config[env];

if (!envConfig) {
    console.error('===');
    console.error(`Database config doesn't exist for "${env}", falling back to "development"!`);
    console.error('===');
    envConfig = config['development'];
}

export default Knex(envConfig);
