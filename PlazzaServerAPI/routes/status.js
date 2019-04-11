const express = require('express');
const router = express.Router();
const fs = require('fs');

/**
 * Get route for status informations
 */
router.get('/', function(req, res) {
    fs.readFile(__dirname + "/../tmp/status.json", (err, data) => {
        if (err) {
            res.send({"error": err.message}).status(500);
        } else {
            let jsonData = {};

            try {
                jsonData = JSON.parse(data.toString());
            } catch (e) {
                res.send({"error": e.message}).status(500);
            }
            res.send({"kitchens": jsonData}).status(200);
        }
    })
});

module.exports = router;
