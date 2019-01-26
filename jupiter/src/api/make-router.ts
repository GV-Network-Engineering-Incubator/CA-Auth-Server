import Router from 'express-promise-router';
import responseDecorators from './middleware/response-decorators';
import hello from './routes/hello';

export default function makeApiRouter() {
  const router = Router();

  router.use(responseDecorators);

  // Add routes here
  router.use(hello);

  return router;
}
