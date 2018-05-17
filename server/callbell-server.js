const notifier = require('node-notifier');
const express = require('express');

const port = 4200;
const app = express();


// POST Request to react when call bell activated
app.post('/call', (req, res) => {

    // TODO: Consider possible request params and handle them

    notifier.notify({
        title: 'Call Bell',
        message: 'You have been summoned!',
        icon: './resources/bell-icon.png',
        wait: false
    });

    res.status(200).send();
});

// Start up the server and listen for incoming connections
app.listen(port, () => {
    console.log(`Started on port ${port}`);
});

