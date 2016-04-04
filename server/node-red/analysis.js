const infos = msg.payload;

if (infos[0] === 'air') {
    if (infos[1] === 'humidity') {
        return [msg, null, null, null, null, null];
    } else if (infos[1] === 'temperature') {
        return [null, msg, null, null, null, null];
    } else if (infos[1] === 'dewpoint') {
        return [null, null, msg, null, null, null];
    }
} else if (infos[0] === 'soil') {
    return [null, null, null, msg, null, null];
} else if (infos[0] === 'light') {
    return [null, null, null, null, msg, null];
} else if (infos[0] === 'water') {
    return [null, null, null, null, null, msg]
}
