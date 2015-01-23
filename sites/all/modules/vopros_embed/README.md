
Vopros embed
============

Allows for embedding a form for submitting a question on another site.

Usage
-----

Assuming a Vopros site at vopros.dk, and a client library site with
agency id 123456, add this script tag on the client site:

```html
  <script src="http://vopros.dk/embed/question_modal.js"></script>
```

And where appropiate, add the link to trigger the popup (note the
agency id in the URL):

```html
  <a href="http://vopros.dk/embed/ask-question?agency_id=DK-123456">Ask a question</a>
```

Further parameters may be supplied, however it might be easier to
supply them from a bit of JavaScript, especially for the user
info. This can be done by defining the variable ask_vopros, whose
values will override the query parameters on the link. Example:

```javascript
var ask_vopros = {
 agency_id: 'DK-123456',
 agency_mail: 'library@example.com',
 name: 'User Realname',
 mail: 'user@example.com',
 phone: '2013456',
 zip: '1927',
 answer_preference: 'chat'
};
```
