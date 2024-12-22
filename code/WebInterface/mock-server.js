/*****************************************************
 *                    MOCK SERVER                    *
 *****************************************************/

const SERVER_LAG_LONG = 1000;
const SERVER_LAG_SHORT = 500;

async function wait(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function serverGet() {
    console.log('serverGet')
    await wait(SERVER_LAG_LONG);
    return [];
}
