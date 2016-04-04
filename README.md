# M2M_E-Grow


## Client

#### Arduino

* Installer l'IDE Arduino sur un ordinateur.
* Brancher l'Arduino "AgriSensor" à celui-ci.
* Ouvrir le dossier AgriSensor dans l'IDE et téléverser le programme sur l'Arduino.
* Répéter cette étape avec l'Arduino "AgriActor" et le dossier AgriActor.
* Brancher les 2 Arduinos aux capteurs via les ports séries et à la 1ère machine via les ports USB.

#### node-red

* Sur une machine externe (idéalement un Raspberry Pi ou équivalent), installer `node-red` :

`sudo apt-get update && sudo apt-get install npm && npm i -g node-red`

* Importer le fichier de configuration de `node-red` :

`Ctrl-Maj-I` > Coller le contenu du fichier `client/node-red/node-red.config`.

* Pour tous les blocs `Serial`, double-cliquer sur ceux-ci et sélectionner les ports USB adéquats.


## Serveur

#### InfluxDB

* Sur une 1ère machine, installer InfluxDB :

`wget http://s3.amazonaws.com/influxdb/influxdb_latest_amd64.deb`
`sudo dpkg -i influxdb_latest_amd64.deb`

* Puis démarrer le service :

`sudo service start influxdb`

* Une interface d'administration est disponible depuis : `http://<IP-machine-1>:8083`

#### Grafana

* Sur une 2e machine (éventuellement la même), installer Grafana :

`wget https://grafanarel.s3.amazonaws.com/builds/grafana_2.6.0_amd64.deb
sudo apt-get install -y adduser libfontconfig
sudo dpkg -i grafana_2.6.0_amd64.deb`

L'interface de Grafana est disponible depuis : `http://<IP-machine-2>:3000`

* Importer le fichier de configuration `server/grafana/grafana.config` dans Grafana :

Menu déroulant (dashboards) > Import > Sélectionner le fichier `grafana.config`.

#### node-red

* Sur une 3e machine (éventuellement la même), installer `node-red` :

`sudo apt-get update && sudo apt-get install npm && npm i -g node-red`

* Importer le fichier de configuration de `node-red` :

`Ctrl-Maj-I` > Coller le contenu du fichier `server/node-red/node-red.config`.

* Eventuellement, changer l'adresse du serveur MQTT de tous les blocs MQTT en double cliquant sur ceux-ci et en configurant l'adresse dans les paramètres du bloc.

* Pour tous les blocs InfluxDB, double-cliquer dessus et entrer l'adresse et le port de la machine sur laquelle est installé InfluxDB.
(Attention: le port d'utilisation à saisir ici (8086) est différent du port d'administration (8083))

* Cliquer sur "Deploy" en haut à droite de l'interface.
