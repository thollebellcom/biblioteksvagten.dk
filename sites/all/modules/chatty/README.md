yarn build
move build/js and build/css folders to static folder.

When deployed:
- pm2 restart chatty

###Testing development
In chatty module folder.

`
npm run dev
`

... opens up http://localhost:3000, with missing params.

Here is a valid URL:
http://localhost:3000/?agency_id=DK-765700&agency_mail=biblioteket%40herning.dk&popup=y&url=https%3A%2F%2Fwww.herningbib.dk%2F

**Only wants to see the backend?**

Apply `renderOnly=backend` to the URL.


**Only wants to see the client?**

Apply `renderOnly=client` to the URL.


** Start server with pm2 **

Run
`
pm2 start index.js --name="chatty" --interpreter=/opt/node/bin/node
`

** Restart server **

Run
`
pm2 restart chatty
`
