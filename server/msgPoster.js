if (msg.payload) {
    msg.payload = +msg.payload[2];
}
return msg;
