import express from 'express';
const router = express.Router();

router.get('/works', (req, res) => {
  res.status(200).send('Hello world from https!');
});

router.get('/breaks', (req, res) => {
  res.status(200).send('Should break');
});
export default router;
