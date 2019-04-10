const express = require('express');
const cookieParser = require('cookie-parser');
const logger = require('morgan');

const statusRouter = require('./routes/status');
const refreshRouter = require('./routes/refresh');
const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use('/status', statusRouter);
app.use('/refresh', refreshRouter);

module.exports = app;
