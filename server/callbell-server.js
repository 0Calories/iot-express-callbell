const notifier = require('node-notifier');
const express = require('express');

const PORT = 4200;
const app = express();

const SUMMON_DELAY = 5000;

let canSummon = true;


// POST Request to react when call bell activated
app.post('/call', (req, res) => {

    // TODO: Consider possible request params and handle them

    if (canSummon) {
        canSummon = false;
        notifier.notify({
            title: 'Call Bell',
            message: 'You have been summoned!',
            icon: './resources/bell-icon.png',
            wait: false
        });

        // Anti spam timeout function
        setTimeout(() => canSummon = true, SUMMON_DELAY);
        res.status(200).send();
    } else {
        res.status(423).send(); // HTTP Status 423 represents 'Locked'
    }
});

// Start up the server and listen for incoming connections
app.listen(PORT, () => {
    console.log(`Started on port ${PORT}`);
});

