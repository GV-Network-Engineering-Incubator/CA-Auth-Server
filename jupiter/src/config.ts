import { hostname } from 'os';

export const NODE_PORT = process.env.NODE_PORT || 3200;

export const JUPITER_DB_HOST = process.env.JUPITER_DB_HOST || '127.0.0.1';
export const JUPITER_DB_PORT = process.env.JUPITER_DB_PORT || '5432';
export const JUPITER_DATABASE = process.env.JUPITER_DATABASE || 'jupiter';
export const JUPITER_DB_USER = process.env.JUPITER_DB_USER || 'postgres';
export const JUPITER_DB_PASSWORD = process.env.JUPITER_DB_PASSWORD || hostname();
export const JUPITER_MIGRATION_DIRECTORY = `${__dirname}/migrations`;
export const JUPITER_DB_SUFFIX = process.env.JUPITER_DB_SUFFIX || 'jupiter';
