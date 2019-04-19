const express = require('express');
const router = express.Router();
const fs = require('fs');

/**
 * Get route for refresh status.json
 */
router.get('/shared', function(req, res) {
    if (!req.query.json) {
        res.send({"error": "invalid query parameter"}).status(500);
    } else {
        let jsonData = {};

        try {
            jsonData = JSON.parse(req.query.json);
        } catch (e) {
            res.send({"error": e.message}).status(500);
        }
        fs.writeFile(__dirname + "/../tmp/status.json", JSON.stringify(jsonData), (err) => {
            if (err) {
                res.send({"error": err.message}).status(500);
            } else {
                res.send({"success": "done"}).status(200);
            }
        })
    }
});

/**
 * Get route for refresh orders.json
 */
router.get('/orders', function(req, res) {
    if (!req.query.json) {
        res.send({"error": "invalid query parameter"}).status(500);
    } else {
        let jsonData = [];

        try {
            jsonData = JSON.parse(req.query.json);
        } catch (e) {
            res.send({"error": e.message}).status(500);
        }
        fs.writeFile(__dirname + "/../tmp/orders.json", JSON.stringify(jsonData), (err) => {
            if (err) {
                res.send({"error": err.message}).status(500);
            } else {
                res.send({"success": "done"}).status(200);
            }
        })
    }
});

module.exports = router;
