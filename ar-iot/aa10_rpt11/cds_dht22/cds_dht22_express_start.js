// cds_dht22_express.js  
// Express
var express = require("express");
var app = express();
var web_port = 3030;  // express port

// MongoDB
var mongoose = require('mongoose');
var Schema = mongoose.Schema;  // Schema object
// MongoDB connection
mongoose.connect('mongodb://127.0.0.1:27017/iot'); // DB name!! 
var db = mongoose.connection;    
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function callback () {
        console.log("mongo db connection OK.");
});

// Schema
var iotSchema = new Schema({
    date: String,
    temperature: String,
    humidity: String,
    luminosity: String,
});
var Sensor = mongoose.model("Sensor", iotSchema);  // sensor data model

// Web routing addrebss
app.get('/', function (req, res) {  // localhost:3030/
  res.send('Hello Arduino IOT: express server by AA10!');
});
// find all data & return them
app.get('/', function (req, res) {
    Sensor.find(function(err, data) {
        res.json(data);
    });
});
// find data by id
app.get('/iot/:id', function (req, res) {
    Sensor.findById(req.params.id, function(err, data) {
        res.json(data);
    });
});

// Express WEB
app.use(express.static(__dirname + "/public"));  // WEB root folder -> public
app.listen(web_port);  // port 3030
console.log("Express_IOT is running at port:3030");
