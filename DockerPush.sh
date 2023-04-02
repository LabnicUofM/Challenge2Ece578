# 1. To create docker image from docker file:
 sudo docker build -t labnic/challenge2ece578 .
# 2. List docker images:
 sudo docker images -a
# 3. Retag the image with a version number: 
 sudo  docker tag labnic/challenge2ece578 labnicuofm/challenge2ece578:version_1
# 4. Docker-Hub login:
 sudo docker login
# 5. Push the local image to docker-hub
 sudo docker push labnicuofm/challenge2ece578:version_1 
# 6. List docker containers:
 sudo docker ps -a
