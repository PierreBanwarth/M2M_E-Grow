const info = msg.payload.split(' ');

const key = info[0].split('/');
const env = key[1];
const car = key[2];

const value = info[1];

msg.payload = [env, car, value];

return msg;
