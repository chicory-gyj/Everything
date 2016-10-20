FROM node:argon
RUN mkdir -p /Users/fangzheng/github/hello/node.js/app
WORKDIR /Users/fangzheng/github/hello/node.js/app
COPY package.json /Users/fangzheng/github/hello/node.js/app
RUN npm install
COPY . /Users/fangzheng/github/hello/node.js/app
EXPOSE 10000
CMD [ "npm", "start" ]
