import get from 'lodash/get';

export default function getNodeEnd() {
  return get(process.env, 'NODE_ENV', 'development');
}
