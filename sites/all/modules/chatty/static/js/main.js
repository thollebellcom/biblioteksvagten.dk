(window.webpackJsonp=window.webpackJsonp||[]).push([[0],{214:function(e,t,n){e.exports=n(542)},498:function(e,t,n){},503:function(e,t,n){},512:function(e,t,n){},535:function(e,t,n){},541:function(e,t,n){},542:function(e,t,n){"use strict";n.r(t);n(215),n(216),n(217),n(218),n(219),n(220),n(221),n(222),n(223),n(224),n(225),n(226),n(227),n(228),n(229),n(230),n(231),n(232),n(233),n(234),n(235),n(236),n(237),n(238),n(239),n(240),n(241),n(95),n(242),n(243),n(244),n(245),n(246),n(247),n(248),n(249),n(250),n(251),n(252),n(253),n(254),n(255),n(256),n(257),n(259),n(260),n(262),n(263),n(265),n(266),n(267),n(132),n(268),n(269),n(270),n(271),n(272),n(273),n(274),n(275),n(276),n(277),n(278),n(279),n(280),n(281),n(282),n(283),n(284),n(285),n(286),n(287),n(288),n(289),n(290),n(291),n(292),n(293),n(294),n(295),n(296),n(297),n(298),n(299),n(300),n(301),n(302),n(303),n(304),n(305),n(306),n(307),n(308),n(309),n(310),n(311),n(312),n(313),n(314),n(315),n(316),n(317),n(319),n(320),n(321),n(322),n(323),n(324),n(325),n(327),n(328),n(329),n(330),n(331),n(332),n(333),n(334),n(335),n(336),n(337),n(187),n(338),n(339),n(189),n(340),n(341),n(342),n(343),n(190),n(344),n(345),n(346),n(347),n(348),n(349),n(350),n(351),n(352),n(353),n(354),n(355),n(356),n(357),n(358),n(359),n(360),n(361),n(362),n(363),n(364),n(365),n(366),n(367),n(368),n(369),n(371),n(372),n(373),n(374),n(375),n(376),n(377),n(378),n(379),n(380),n(381),n(382),n(383),n(384),n(385),n(386),n(387),n(388),n(389),n(390),n(391),n(392),n(393),n(394),n(395),n(396),n(397),n(398),n(399),n(400),n(401),n(402),n(403),n(140),n(404),n(405),n(406),n(407),n(408),n(409),n(410),n(412),n(413),n(414),n(415),n(416),n(417),n(418),n(419),n(421),n(422),n(423),n(424),n(425),n(426),n(427),n(428),n(429),n(430),n(431),n(432),n(433),n(434),n(435),n(436),n(437),n(438),n(439),n(440),n(441),n(442),n(443),n(444),n(445),n(447),n(448),n(449),n(450),n(451),n(452),n(453),n(454),n(455),n(456),n(457),n(458),n(459),n(460),n(461),n(462),n(463),n(464),n(465),n(466),n(467),n(468),n(469),n(470),n(471),n(472),n(473),n(474),n(475),n(476),n(477),n(478),n(480),n(481),n(482),n(483),n(484),n(485),n(486),n(487),n(488),n(489),n(490),n(491),n(492),n(493),n(494),n(495),n(497),n(200),n(498);var a=n(0),r=n.n(a),s=n(87),c=n.n(s),u=function(e){for(var t=window.location.search.substring(1).split("&"),n=0;n<t.length;n++){var a=t[n].split("=");if(a[0]===e)return a[1]}return""},i=n(6),o=n(21),l=r.a.createContext(),d=function(e,t){switch(t.type){case"RESET_CHAT":return localStorage.removeItem("clientActiveQuestionId"),Object(o.a)({},e,{clientChat:null});case"SET_ACTIVE_CHAT":return localStorage.setItem("clientActiveQuestionId",t.payload),Object(o.a)({},e,{clientChat:{questionId:t.payload}});default:return e}},m=function(e){var t=e.children,n=Object(a.useReducer)(d,{clientChat:null}),s=Object(i.a)(n,2),c=s[0],u=s[1];return Object(a.useEffect)(function(){var e=localStorage.getItem("clientActiveQuestionId");e&&u({type:"SET_ACTIVE_CHAT",payload:e})},[]),r.a.createElement(l.Provider,{value:[c,u]},t)},b=(n(503),n(23)),f=n(15),v=n(16),E=n.n(v);function g(){var e=Object(f.a)(["\n  mutation CreateQuestionMutation(\n    $agencyId: String!\n    $agencyMail: String!\n    $authorName: String!\n    $authorEmail: String!\n    $subject: String!\n    $url: String!\n  ) {\n    createQuestion(\n      data: {\n        authorName: $authorName\n        authorEmail: $authorEmail\n        agencyMail: $agencyMail\n        agencyId: $agencyId\n        subject: $subject\n        url: $url\n      }\n    ) {\n      id\n      subject\n      authorName\n      status\n    }\n  }\n"]);return g=function(){return e},e}var p=E()(g()),_=function(e){var t=e.createQuestion,n=e.loading,s=Object(a.useRef)(""),c=Object(a.useRef)(""),i=Object(a.useRef)(""),o=n;return r.a.createElement("form",{onSubmit:function(e){e.preventDefault();var n=u("agency_id"),a=u("agency_mail"),r=u("url");if(!n||!r)return alert("A needed param was not set.");t({variables:{agencyId:n,agencyMail:a,authorName:s.current.value,authorEmail:c.current.value,subject:i.current.value,url:r}})}},r.a.createElement("div",{className:"question-form__input-wrapper question-form__input-wrapper--question"},r.a.createElement("label",null,"Hvad vil du sp\xf8rge om?"),r.a.createElement("div",null,r.a.createElement("textarea",{autoFocus:!0,disabled:o,rows:"5",ref:i}))),r.a.createElement("div",{className:"question-form__input-wrapper question-form__input-wrapper--name"},r.a.createElement("label",null,"Dit navn",r.a.createElement("div",null,r.a.createElement("input",{type:"text",disabled:o,ref:s,required:!0})))),r.a.createElement("div",{className:"question-form__input-wrapper question-form__input-wrapper--email"},r.a.createElement("label",null,"Din e-mail adresse",r.a.createElement("div",null,r.a.createElement("input",{type:"email",disabled:o,ref:c,required:!0})))),r.a.createElement("input",{type:"submit",value:"Sp\xf8rg nu"}))},q=function(){var e=Object(a.useContext)(l),t=Object(i.a)(e,2)[1];return r.a.createElement("div",{className:"question-form"},r.a.createElement(b.b,{mutation:p},function(e,n){var a=n.loading,s=n.data;return s&&s.createQuestion.id&&t({type:"SET_ACTIVE_CHAT",payload:s.createQuestion.id}),r.a.createElement(_,{createQuestion:e,loading:a})}))};n(512);function j(){var e=Object(f.a)(["\n  query QuestionQuery($questionId: ID!) {\n    question(questionId: $questionId) {\n      id\n      subject\n      authorName\n      authorEmail\n      consultant\n      status\n      source\n      lastHeartbeatAt\n      createdAt\n      messages {\n        id\n        text\n        sentFrom\n        createdAt\n      }\n    }\n  }\n"]);return j=function(){return e},e}var h=E()(j());function I(){var e=Object(f.a)(["\n  mutation CreateMessageMutation($questionId: ID!, $sentFrom: String!, $text: String!) {\n    createMessage(questionId: $questionId, data: { text: $text, sentFrom: $sentFrom }) {\n      id\n      text\n      sentFrom\n      createdAt\n      question {\n        id\n        authorName\n      }\n    }\n  }\n"]);return I=function(){return e},e}var O=E()(I()),y=r.a.createContext(),k=function(e,t){switch(t.type){case"RESET_CHAT":return localStorage.removeItem("backendActiveQuestionId"),Object(o.a)({},e,{backendChat:null});case"SET_ACTIVE_CHAT":return localStorage.setItem("backendActiveQuestionId",t.payload),Object(o.a)({},e,{backendChat:{questionId:t.payload,message:""}});case"SET_CHAT_MESSAGE_TEXT":return Object(o.a)({},e,{backendChat:Object(o.a)({},e.backendChat,{message:t.payload})});default:return e}},S=function(e){var t=e.children,n=Object(a.useReducer)(k,{backendChat:null}),s=Object(i.a)(n,2),c=s[0],u=s[1];return Object(a.useEffect)(function(){var e=localStorage.getItem("backendActiveQuestionId");e&&u({type:"SET_ACTIVE_CHAT",payload:e})},[]),r.a.createElement(y.Provider,{value:[c,u]},t)};function C(){var e=Object(f.a)(["\n  mutation MakeHeartbeatMutation($questionId: ID!) {\n    makeHeartbeat(questionId: $questionId) {\n      id\n    }\n  }\n"]);return C=function(){return e},e}var N=E()(C()),A=r.a.createContext(),T=function(e,t){switch(t.type){case"RESET_SETTINGS":return localStorage.removeItem("clientSettings"),{};case"SET_SETTINGS":return localStorage.setItem("clientSettings",JSON.stringify(t.payload)),Object(o.a)({},t.payload,{messages:JSON.parse(t.payload.messages),standardAnswers:JSON.parse(t.payload.standardAnswers)});default:return e}},w=function(e){var t=e.children,n=Object(a.useReducer)(T,{}),s=Object(i.a)(n,2),c=s[0],u=s[1];return Object(a.useEffect)(function(){var e=localStorage.getItem("clientSettings");e&&u({type:"SET_SETTINGS",payload:JSON.parse(e)})},[]),r.a.createElement(A.Provider,{value:[c,u]},t)},D=function(e){var t=e.status,n=Object(a.useContext)(A),s=Object(i.a)(n,1)[0];return"pending"===t?r.a.createElement("div",{className:"client-status-bar client-status-bar--".concat(t)},s.messages.chatPending):""},x=n(60);function Q(){var e=Object(f.a)(["\n  subscription NewMessageSubscription($questionId: ID!) {\n    newMessage(questionId: $questionId) {\n      id\n      text\n      sentFrom\n      createdAt\n      question {\n        id\n        authorName\n      }\n    }\n  }\n"]);return Q=function(){return e},e}var $=E()(Q());function H(){var e=Object(f.a)(["\n  subscription QuestionClosedSubscription($questionId: ID!) {\n    questionClosed(questionId: $questionId) {\n      id\n      status\n      subject\n      authorName\n      authorEmail\n      consultant\n      source\n      createdAt\n      lastHeartbeatAt\n      messages {\n        id\n        text\n        sentFrom\n        createdAt\n      }\n    }\n  }\n"]);return H=function(){return e},e}var M=E()(H());function R(){var e=Object(f.a)(["\n  subscription QuestionAssignedSubscription($questionId: ID) {\n    questionAssigned(questionId: $questionId) {\n      status\n    }\n  }\n"]);return R=function(){return e},e}var F=E()(R());function V(){var e=Object(f.a)(["\n  subscription QuestionReopenedSubscription($questionId: ID) {\n    questionReopened(questionId: $questionId) {\n      id\n      status\n      consultant\n      subject\n      authorName\n      authorEmail\n      source\n      createdAt\n      lastHeartbeatAt\n    }\n  }\n"]);return V=function(){return e},e}var B=E()(V()),G=function(e){return new Date(1e3*e)},J=n(147),P=n.n(J),K=n(148),X=n.n(K),Y=function(e){var t=X()(e,"DD.MM.YYYY",{locale:P.a}),n=X()(e,"HH:mm",{locale:P.a});return"D. ".concat(t," kl. ").concat(n)},L=function(e){var t=e.sentFrom,n=e.text,s=e.createdAt,c=G(s),u=Object(a.useState)(Y(c)),o=Object(i.a)(u,2),l=o[0],d=o[1];return Object(a.useEffect)(function(){var e=setInterval(function(){d(Y(c))},3e4);return function(){return clearInterval(e)}}),r.a.createElement("div",{className:"client-message client-message--".concat(t)},r.a.createElement("div",{className:"client-message__box"},r.a.createElement("div",{className:"client-message__text"},n)),"system"===t?"":r.a.createElement("div",{className:"client-message__created-at"},l))},z=function(e){if(0===e.length)return!1;var t=e.scrollHeight;e.scrollTop=t},U=function(e){var t=e.disabled,n=e.subject,s=e.questionCreatedAt,c=e.messages,u=e.subscribeToMore,d=e.makeHeartbeat,m=Object(a.useContext)(l),b=Object(i.a)(m,2),f=b[0],v=b[1];Object(a.useEffect)(function(){u({document:$,variables:{questionId:f.clientChat.questionId},updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=Object.assign({},e,Object(o.a)({},e,{question:Object(o.a)({},e.question,{messages:[n.data.newMessage]})}));return e.question.messages&&(a.question.messages=[].concat(Object(x.a)(e.question.messages),[n.data.newMessage])),a}}),u({document:F,variables:{questionId:f.clientChat.questionId},updateQuery:function(e,t){var n=t.subscriptionData;return n.data?Object.assign({},e,Object(o.a)({},e,{question:Object(o.a)({},e.question,{},n.data.questionAssigned)})):e}}),u({document:M,variables:{questionId:f.clientChat.questionId},updateQuery:function(e,t){return t.subscriptionData.data?(v({type:"RESET_CHAT",payload:null}),Object.assign({},e,Object(o.a)({},e,{question:null}))):e}}),u({document:B,variables:{questionId:f.clientChat.questionId},updateQuery:function(e,t){var n=t.subscriptionData;return n.data?Object.assign({},e,Object(o.a)({},e,{question:Object(o.a)({},e.question,{},n.data.questionReopened)})):e}})},[]),Object(a.useEffect)(function(){var e=setInterval(function(){d({variables:{questionId:f.clientChat.questionId}})},1e4);return function(){return clearInterval(e)}}),Object(a.useEffect)(function(){z(document.querySelector(".client-messages"))});return r.a.createElement("div",{className:t?"client-messages client-messages--disabled":"client-messages"},function(){if(t)return r.a.createElement("div",{className:"loading"},r.a.createElement("div",null),r.a.createElement("div",null))}(),r.a.createElement(L,{text:n,createdAt:s,sentFrom:"user"}),c.map(function(e,t){return r.a.createElement("div",{key:"client-message-".concat(t,"-").concat(e.id)},r.a.createElement(L,{text:e.text,createdAt:e.createdAt,sentFrom:e.sentFrom}))}))},W=n(112),Z=function(e){var t=e.createMessage,n=e.disabled,s=Object(a.useContext)(l),c=Object(i.a)(s,1)[0],u=Object(a.useState)(""),o=Object(i.a)(u,2),d=o[0],m=o[1],b=Object(a.useRef)();return r.a.createElement("div",{className:"client-form"},r.a.createElement("form",{onSubmit:function(e){e.preventDefault(),""!==d&&(t({variables:{questionId:c.clientChat.questionId,text:d,sentFrom:"user"}}),m(""))},ref:b},r.a.createElement(W.a,{minRows:2,maxRows:5,value:d,placeholder:"Indtast din besked...",onChange:function(e){return m(e.target.value)},onKeyDown:function(e){13!==e.keyCode||13===e.keyCode&&e.shiftKey||(e.preventDefault(),b.current.dispatchEvent(new Event("submit")))},disabled:n,autoFocus:!0}),r.a.createElement("input",{type:"submit",value:"Send besked"})))},ee=function(){var e=Object(a.useContext)(l),t=Object(i.a)(e,2),n=t[0],s=t[1];return r.a.createElement(b.c,{query:h,variables:{questionId:n.clientChat.questionId}},function(e){var t=e.data,n=e.loading,a=e.subscribeToMore;if(!t||n)return"";var c=t.question.status,u="pending"===c||"complete"===c;return"complete"===t.question.status&&s({type:"RESET_CHAT",payload:null}),r.a.createElement("div",{className:"client-chat"},r.a.createElement(D,{status:t.question.status}),r.a.createElement(b.b,{mutation:N},function(e){return r.a.createElement(U,{disabled:u,subject:t.question.subject,questionCreatedAt:t.question.createdAt,messages:t.question.messages,subscribeToMore:a,makeHeartbeat:e})}),r.a.createElement(b.b,{mutation:O},function(e){return r.a.createElement(Z,{disabled:u,createMessage:e})}))})},te=function(){var e=Object(a.useContext)(l);return Object(i.a)(e,1)[0].clientChat?r.a.createElement(ee,null):r.a.createElement(q,null)},ne=n(67),ae=n(212),re=n(38),se=n(213),ce=n(210),ue=n(3),ie=n(149),oe=new se.a({uri:"https://new.biblioteksvagten.dk/graphql",fetch:ie.a}),le=new ce.a({uri:"wss://new.biblioteksvagten.dk/graphql",fetch:ie.a,options:{reconnect:!0}}),de=Object(re.d)(function(e){var t=e.query,n=Object(ue.l)(t);return"OperationDefinition"===n.kind&&"subscription"===n.operation},le,oe),me=new ae.a,be=new ne.c({link:de,cache:me}),fe=function(e){var t=e.children;return r.a.createElement(b.a,{client:be},t)},ve=function(e){var t=e.children;return r.a.createElement(w,null,r.a.createElement(m,null,t))};function Ee(){var e=Object(f.a)(["\n  query {\n    settings {\n      messages\n      standardAnswers\n    }\n  }\n"]);return Ee=function(){return e},e}var ge=E()(Ee()),pe=function(e){var t=e.children,n=e.data,r=e.loading,s=Object(a.useContext)(A),c=Object(i.a)(s,2)[1];return Object(a.useEffect)(function(){n&&!r&&c({type:"SET_SETTINGS",payload:n.settings})},[]),t},_e=function(e){var t=e.children;return r.a.createElement(b.c,{query:ge},function(e){var n=e.data,a=e.loading;return!n||a?t:r.a.createElement(pe,{data:n,loading:a},t)})},qe=function(){return r.a.createElement(fe,null,r.a.createElement(ve,null,r.a.createElement(_e,null,r.a.createElement(te,null))))};n(535);function je(){var e=Object(f.a)(["\n  query QuestionsQuery($statusType: String!, $consultantId: ID) {\n    questions(statusType: $statusType, consultantId: $consultantId) {\n      id\n      subject\n      authorName\n      authorEmail\n      consultant\n      status\n      source\n      lastHeartbeatAt\n      createdAt\n    }\n  }\n"]);return je=function(){return e},e}var he=E()(je());function Ie(){var e=Object(f.a)(["\n  subscription NewQuestionSubscription($statusType: String!) {\n    newQuestion(statusType: $statusType) {\n      id\n      status\n      subject\n      authorName\n      authorEmail\n      source\n      consultant\n      createdAt\n      lastHeartbeatAt\n    }\n  }\n"]);return Ie=function(){return e},e}var Oe=E()(Ie());function ye(){var e=Object(f.a)(["\n  subscription QuestionAssignedToConsultantSubscription($consultantId: ID) {\n    questionAssignedToConsultant(consultantId: $consultantId) {\n      id\n      status\n      subject\n      authorName\n      authorEmail\n      consultant\n      source\n      createdAt\n      lastHeartbeatAt\n    }\n  }\n"]);return ye=function(){return e},e}var ke=E()(ye()),Se=n(89),Ce=n.n(Se);function Ne(){var e=Object(f.a)(["\n  mutation AssignQuestionMutation($questionId: ID!, $consultantId: ID!) {\n    assignQuestion(questionId: $questionId, consultantId: $consultantId) {\n      id\n      subject\n      authorName\n      createdAt\n    }\n  }\n"]);return Ne=function(){return e},e}var Ae=E()(Ne()),Te=n(211),we=n.n(Te),De=function(e){var t=G(e);return we()(new Date,t)>15},xe=function(e){var t=e.canAssign,n=e.canSetActive,s=e.questionId,c=e.heading,u=e.text,o=e.source,l=e.isActive,d=e.createdAt,m=e.lastHeartbeat,f=e.subscribeToMore,v=G(d),E=window.Drupal&&window.Drupal.settings&&window.Drupal.settings.consultantId?window.Drupal.settings.consultantId.toString():"1",g=Object(a.useState)(!1),p=Object(i.a)(g,2),_=p[0],q=p[1],j=Object(a.useState)(Y(v)),h=Object(i.a)(j,2),I=h[0],O=h[1],k=Object(a.useState)(De(m)),S=Object(i.a)(k,2),C=S[0],N=S[1],A=Object(a.useContext)(y),T=Object(i.a)(A,2),w=T[0],D=T[1];Object(a.useEffect)(function(){var e=setInterval(function(){O(Y(v))},3e4);return function(){return clearInterval(e)}}),Object(a.useEffect)(function(){var e=setInterval(function(){N(De(m))},1e4);return function(){return clearInterval(e)}}),Object(a.useEffect)(function(){f({document:$,variables:{questionId:s},updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.newMessage;return"admin"===a.sentFrom?(q(!1),e):w.backendChat&&w.backendChat.questionId&&w.backendChat.questionId===a.question.id?(q(!1),e):(q(!0),e)}})},[w]);return c=C?Ce()(c,20)+" (offline)":Ce()(c,32),r.a.createElement(b.b,{mutation:Ae},function(e){return r.a.createElement("div",{className:"question question--teaser ".concat(l&&"question--active"),onClick:function(){var a;t&&(a=e,window.confirm("Vil du overtage dette sp\xf8rgsm\xe5l?")&&a({variables:{questionId:s,consultantId:E}})),n&&(D({type:"SET_ACTIVE_CHAT",payload:s}),q(!1))}},r.a.createElement("div",{className:"question__heading"},r.a.createElement("div",{className:"question__heading__title"},c)),r.a.createElement("div",{className:"question__body"},Ce()(u,35)),r.a.createElement("div",{className:"question__source"},Ce()(o,35)),r.a.createElement("small",{className:"question__created-at"},I),_&&r.a.createElement("small",{className:"question__unread-messages"},"Der er ul\xe6ste beskeder"))})},Qe=function(e){var t=e.canAssign,n=e.canSetActive,s=e.title,c=e.questions,u=e.subscriptions,o=e.subscribeToMore,l=window.Drupal&&window.Drupal.settings&&window.Drupal.settings.consultantId?window.Drupal.settings.consultantId.toString():"1",d=Object(a.useContext)(y),m=Object(i.a)(d,2),b=m[0];m[1];Object(a.useEffect)(function(){for(var e=0;e<u.length;e++)u[e]()},[]);return r.a.createElement("div",{className:"backend-list"},r.a.createElement("div",{className:"backend-list__heading"},r.a.createElement("h4",{className:"backend-list__heading__title"},s)),r.a.createElement("div",{className:"backend-list__body"},c&&0!==c.length?c.sort(function(e,t){return e.id>t.id?1:-1}).map(function(e){return r.a.createElement("div",{className:l!==e.consultant?"backend-list__item backend-list__item--faded":"backend-list__item",key:"question-".concat(e.id)},r.a.createElement(xe,{questionId:e.id,heading:e.authorName,text:e.subject,createdAt:e.createdAt,canAssign:t,canSetActive:n,lastHeartbeat:e.lastHeartbeatAt,readOnly:l!==e.consultant,subscribeToMore:o,isActive:b.backendChat&&b.backendChat.questionId===e.id}))}):r.a.createElement("div",{className:"backend-list__item backend-list__item--no-result"},"Ingen samtaler at vise.")))};function $e(){var e=Object(f.a)(["\n  subscription QuestionHeartbeatSubscription($questionId: ID) {\n    questionHeartbeat(questionId: $questionId) {\n      id\n      lastHeartbeatAt\n    }\n  }\n"]);return $e=function(){return e},e}var He=E()($e()),Me=function(){var e=[];return r.a.createElement(b.c,{query:he,variables:{consultantId:null,statusType:"pending"}},function(t){var n=t.loading,a=t.data,s=t.subscribeToMore;return a?n?"Henter...":(e.push(function(){return s({document:Oe,variables:{consultantId:null,statusType:"pending"},updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.newQuestion;return Object.assign({},e,{questions:[].concat(Object(x.a)(e.questions),[a])})}})}),e.push(function(){return s({document:ke,updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.questionAssignedToConsultant,r=e.questions.filter(function(e){return e.id!==a.id});return Object.assign({},e,{questions:r})}})}),e.push(function(){return s({document:B,updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.questionReopened,r=e.questions.filter(function(e){return e.id!==a.id});return r.push(a),Object.assign({},e,{questions:r})}})}),e.push(function(){return s({document:He,updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.questionHeartbeat,r=e.questions.find(function(e){return e.id===a.id});if(!r)return e;var s=Object(o.a)({},r),c=e.questions.filter(function(e){return e.id!==a.id});return c.push(s),Object.assign({},e,{questions:c})}})}),r.a.createElement(Qe,{title:"Chats, Afventer svar",questions:a.questions,subscriptions:e,subscribeToMore:s,canAssign:!0,canSetActive:!0})):""})};function Re(){var e=Object(f.a)(["\n  subscription AssignedQuestionClosedSubscription($consultantId: ID) {\n    assignedQuestionClosed(consultantId: $consultantId) {\n      id\n      status\n      subject\n      authorName\n      authorEmail\n      consultant\n      source\n      createdAt\n      lastHeartbeatAt\n    }\n  }\n"]);return Re=function(){return e},e}var Fe=E()(Re()),Ve=function(){var e=[];return r.a.createElement(b.c,{query:he,variables:{statusType:"assigned",consultantId:null}},function(t){var n=t.loading,a=t.data,s=t.subscribeToMore;return a?n?"Henter...":(e.push(function(){return s({document:ke,updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.questionAssignedToConsultant;return Object.assign({},e,{questions:[].concat(Object(x.a)(e.questions),[a])})}})}),e.push(function(){return s({document:Fe,updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.assignedQuestionClosed,r=e.questions.filter(function(e){return e.id!==a.id});return Object.assign({},e,{questions:r})}})}),e.push(function(){return s({document:B,updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.questionReopened,r=e.questions.filter(function(e){return e.id!==a.id});return Object.assign({},e,{questions:r})}})}),e.push(function(){return s({document:He,updateQuery:function(e,t){var n=t.subscriptionData;if(!n.data)return e;var a=n.data.questionHeartbeat,r=e.questions.find(function(e){return e.id===a.id});if(!r)return e;var s=Object(o.a)({},r),c=e.questions.filter(function(e){return e.id!==a.id});return c.push(s),Object.assign({},e,{questions:c})}})}),r.a.createElement(Qe,{title:"Chats, Ved at blive besvaret",questions:a.questions,subscriptions:e,subscribeToMore:s,canAssign:!1,canSetActive:!0})):""})},Be=function(){return r.a.createElement("div",{className:"backend-sidebar"},r.a.createElement(Me,null),r.a.createElement(Ve,null))},Ge=(n(541),function(e){var t=e.lastHeartbeat,n=Object(a.useState)(De(t)),s=Object(i.a)(n,2),c=s[0],u=s[1];return Object(a.useEffect)(function(){var e=setInterval(function(){u(De(t))},1e4);return function(){return clearInterval(e)}}),c?r.a.createElement("div",{className:"backend-notice backend-notice--offline"},"Brugeren er offline..."):r.a.createElement(r.a.Fragment,null)}),Je=function(){return r.a.createElement("div",{className:"backend-notice backend-notice--readonly"},"Du observerer en chat der er tildelt en anden bruger.")},Pe=function(e){var t=e.name,n=e.email,s=e.source,c=Object(a.useContext)(y),u=Object(i.a)(c,2)[1];return r.a.createElement("div",{className:"backend-bar"},r.a.createElement("div",{className:"backend-bar__heading"},r.a.createElement("h2",null,t),r.a.createElement("h3",null,r.a.createElement("a",{href:"mailto:".concat(n)},n)),r.a.createElement("h4",null,s)),r.a.createElement("div",{className:"backend-bar__spacer"}),r.a.createElement("span",{className:"backend-bar__button bar__button--close",onClick:function(){u({type:"RESET_CHAT",payload:null})},title:"Klik for at lukke"},"X"))},Ke=function(e){var t=e.sentFrom,n=e.submittedBy,s=e.text,c=e.createdAt,u=G(c),o=Object(a.useState)(Y(u)),l=Object(i.a)(o,2),d=l[0],m=l[1];return Object(a.useEffect)(function(){var e=setInterval(function(){m(Y(u))},3e4);return function(){return clearInterval(e)}}),r.a.createElement("div",{className:"backend-message backend-message--".concat(t)},r.a.createElement("div",{className:"backend-message__box"},r.a.createElement("div",{className:"backend-message__text"},s)),n&&r.a.createElement("div",{className:"backend-message__submitted-by"},"Af ",n),"system"===t?"":r.a.createElement("div",{className:"backend-message__created-at"},d))},Xe=function(e){var t=e.author,n=e.subject,s=e.questionCreatedAt,c=e.messages,u=e.subscribeToMore,l=Object(a.useContext)(y),d=Object(i.a)(l,1)[0],m=window.Drupal&&window.Drupal.settings&&window.Drupal.settings.consultantName?window.Drupal.settings.consultantName.toString():"ikke defineret";Object(a.useEffect)(function(){u({document:$,variables:{questionId:d.backendChat.questionId},updateQuery:function(e,t){var n=t.subscriptionData;return n.data?Object.assign({},e,Object(o.a)({},e,{question:Object(o.a)({},e.question,{messages:[].concat(Object(x.a)(e.question.messages),[n.data.newMessage])})})):e}})},[]),Object(a.useEffect)(function(){z(document.querySelector(".backend-chat__messages"))});return r.a.createElement("div",{className:"backend-chat__messages"},r.a.createElement(Ke,{text:n,createdAt:s,sentFrom:"user"}),c.map(function(e,n){var a="";return"admin"===e.sentFrom?a=m:"user"===e.sentFrom&&(a=t),r.a.createElement("div",{key:"backend-message-".concat(n,"-").concat(e.id)},r.a.createElement(Ke,{submittedBy:a,text:e.text,createdAt:e.createdAt,sentFrom:e.sentFrom}))}))};function Ye(){var e=Object(f.a)(["\n  mutation CloseQuestionMutation(\n    $questionId: ID!\n    $reason: String!\n    $keepConsultant: Boolean\n    $title: String\n  ) {\n    closeQuestion(\n      questionId: $questionId\n      reason: $reason\n      keepConsultant: $keepConsultant\n      title: $title\n    ) {\n      id\n      subject\n      authorName\n      createdAt\n      messages {\n        id\n        text\n        sentFrom\n        createdAt\n      }\n    }\n  }\n"]);return Ye=function(){return e},e}var Le=E()(Ye());function ze(){var e=Object(f.a)(["\n  mutation ReopenQuestionMutation($questionId: ID!) {\n    reopenQuestion(questionId: $questionId) {\n      id\n    }\n  }\n"]);return ze=function(){return e},e}var Ue=E()(ze()),We=function(e){var t=e.children,n=e.title,a=e.toggle,s=e.visible;return r.a.createElement("div",{className:"overlay ".concat(s?"overlay--visible":"")},r.a.createElement("div",{className:"modal"},r.a.createElement("div",{className:"modal__heading"},r.a.createElement("h1",{className:"modal__heading__title"},n)),r.a.createElement("div",{className:"modal__body"},t),r.a.createElement("div",{className:"modal__footer"},r.a.createElement("button",{className:"modal__footer__button",onClick:function(){return a(!s)}},"Luk vindue"))))},Ze=function(e){var t=e.closeQuestion,n=e.confirmText,s=e.text,c=e.reason,u=e.data,o=e.loading,l=Object(a.useContext)(y),d=Object(i.a)(l,2),m=d[0],b=d[1];!o&&u&&u.closeQuestion.id&&b({type:"RESET_CHAT",payload:null});var f=function(e){e.preventDefault(),window.confirm(n)&&t({variables:{reason:c,questionId:m.backendChat.questionId}})};return o?r.a.createElement("button",{className:"backend-chat__button backend-chat__button--close-question",onClick:f,disabled:!0},"Vent venligst..."):r.a.createElement("button",{className:"backend-chat__button backend-chat__button--close-question",onClick:f},s)},et=function(e){var t=e.reopenQuestion,n=Object(a.useContext)(y),s=Object(i.a)(n,2),c=s[0],u=s[1];return r.a.createElement("button",{className:"backend-chat__button backend-chat__button--reopen-question",onClick:function(e){e.preventDefault(),window.confirm("Vil du gen\xe5bne dette sp\xf8rgsm\xe5l?")&&(t({variables:{questionId:c.backendChat.questionId}}),u({type:"RESET_CHAT",payload:null}))}},"Forlad chat")},tt=function(e){var t=e.closeQuestion,n=e.data,s=e.loading,c=Object(a.useContext)(y),u=Object(i.a)(c,2),o=u[0],l=u[1],d=Object(a.useState)(!1),m=Object(i.a)(d,2),b=m[0],f=m[1],v=Object(a.useRef)(""),E=Object(a.useRef)("");!s&&n&&n.closeQuestion.id&&l({type:"RESET_CHAT",payload:null});return s?r.a.createElement("button",{className:"backend-chat__button backend-chat__button--answer-later",disabled:!0},"Vent venligst..."):r.a.createElement("div",null,r.a.createElement("button",{className:"backend-chat__button backend-chat__button--answer-later",onClick:function(e){e.preventDefault(),window.confirm("Vil du besvare dette sp\xf8rgsm\xe5l senere?")&&f(!0)}},"Besvar senere"),b&&r.a.createElement("form",{onSubmit:function(e){e.preventDefault(),t({variables:{questionId:o.backendChat.questionId,reason:"later",title:v.current.value,keepConsultant:E.current.checked}}),f(!1)}},r.a.createElement("div",null,r.a.createElement("strong",null,"Der er behov for ekstra informationer."),r.a.createElement("div",null,r.a.createElement("label",{htmlFor:"title"},"Titel"),r.a.createElement("input",{type:"text",id:"title",ref:v})),r.a.createElement("div",null,r.a.createElement("label",{htmlFor:"keepConsultant"},r.a.createElement("input",{type:"checkbox",id:"keepConsultant",ref:E}),"Jeg besvarer selv sp\xf8rgsm\xe5let"))),r.a.createElement("button",{type:"submit"},"Send")))},nt=r.a.createContext(),at=function(e,t){switch(t.type){case"RESET_SETTINGS":return localStorage.removeItem("backendSettings"),{};case"SET_SETTINGS":return localStorage.setItem("backendSettings",JSON.stringify(t.payload)),Object(o.a)({},t.payload,{messages:JSON.parse(t.payload.messages),standardAnswers:JSON.parse(t.payload.standardAnswers)});default:return e}},rt=function(e){var t=e.children,n=Object(a.useReducer)(at,{messages:null,standardAnswers:null}),s=Object(i.a)(n,2),c=s[0],u=s[1];return Object(a.useEffect)(function(){var e=localStorage.getItem("backendSettings");e&&u({type:"SET_SETTINGS",payload:JSON.parse(e)})},[]),r.a.createElement(nt.Provider,{value:[c,u]},t)},st=function(e){var t=e.modalToggle,n=e.modalVisible,s=Object(a.useContext)(nt),c=Object(i.a)(s,1)[0],u=Object(a.useContext)(y),o=Object(i.a)(u,2)[1],l=c.standardAnswers,d=Object.keys(l).map(function(e,a){var s=e,c=l[e],u=Object.keys(c).map(function(e,a){var s=e,u=c[e];return r.a.createElement("div",{className:"standard-answer",key:"answer-item-".concat(e,"-").concat(a),onClick:function(){return function(e){o({type:"SET_CHAT_MESSAGE_TEXT",payload:e}),t(!n),document.querySelector(".backend-form textarea").focus()}(u)}},r.a.createElement("div",{className:"standard-answer__heading"},r.a.createElement("h4",{className:"standard-answer__heading__title"},s)),r.a.createElement("div",{className:"standard-answer__text"},u))});return r.a.createElement("div",{className:"standard-answer-list__item",key:"answer-".concat(e,"-").concat(a)},r.a.createElement("div",{className:"standard-answer-list__item__heading"},r.a.createElement("h3",{className:"standard-answer-list__item__heading__title"},s)),r.a.createElement("div",{className:"standard-answer-list__item__content"},u))});return r.a.createElement("div",{className:"standard-answer-list"},d)},ct=function(){var e=Object(a.useState)(!1),t=Object(i.a)(e,2),n=t[0],s=t[1],c=Object(a.useState)(!1),u=Object(i.a)(c,2),o=u[0],l=u[1],d=function(e){l(!1),s(e)},m=function(e){s(!1),l(e)};return r.a.createElement("div",{className:"backend-chat__actions"},r.a.createElement("div",{className:"button-list"},r.a.createElement("div",{className:"button-list__item"},r.a.createElement(We,{toggle:d,visible:n,title:"Standard svar"},r.a.createElement(st,{modalToggle:d,modalVisible:n})),r.a.createElement("button",{className:"backend-chat__button",onClick:function(){return d(!n)}},"Standard svar")),r.a.createElement("div",{className:"button-list__item"},r.a.createElement("button",{className:"backend-chat__button",onClick:function(){return m(!o)}},"Afslut samtale"),r.a.createElement(We,{toggle:m,visible:o,title:"Afslut samtalen"},r.a.createElement("div",{className:"button-list"},r.a.createElement("div",{className:"button-list__item"},r.a.createElement(b.b,{mutation:Ue},function(e){return r.a.createElement(et,{reopenQuestion:e})})),r.a.createElement("div",{className:"button-list__item"},r.a.createElement(b.b,{mutation:Le},function(e,t){var n=t.loading,a=t.data;return r.a.createElement(Ze,{text:"Luk grundet spam",confirmText:"Vil du lukke dette sp\xf8rgsm\xe5l og markere sp\xf8rgsm\xe5let som spam?",reason:"spam",closeQuestion:e,loading:n,data:a})})),r.a.createElement("div",{className:"button-list__item"},r.a.createElement(b.b,{mutation:Le},function(e,t){var n=t.loading,a=t.data;return r.a.createElement(Ze,{text:"Luk som besvaret",confirmText:"Vil du lukke dette sp\xf8rgsm\xe5l og markere sp\xf8rgsm\xe5let som besvaret?",reason:"answered",closeQuestion:e,loading:n,data:a})})),r.a.createElement("div",{className:"button-list__item"},r.a.createElement(b.b,{mutation:Le},function(e,t){var n=t.loading,a=t.data;return r.a.createElement(tt,{closeQuestion:e,loading:n,data:a})})))))))},ut=function(e){var t=e.createMessage,n=Object(a.useContext)(y),s=Object(i.a)(n,2),c=s[0],u=s[1],o=Object(a.useRef)();return r.a.createElement("div",{className:"backend-form"},r.a.createElement("form",{onSubmit:function(e){e.preventDefault(),""!==c.backendChat.message&&(t({variables:{questionId:c.backendChat.questionId,text:c.backendChat.message,sentFrom:"admin"}}),u({type:"SET_CHAT_MESSAGE_TEXT",payload:""}))},ref:o},r.a.createElement(W.a,{minRows:2,maxRows:5,value:c.backendChat.message,placeholder:"Indtast din besked...",onChange:function(e){u({type:"SET_CHAT_MESSAGE_TEXT",payload:e.target.value})},onKeyDown:function(e){13!==e.keyCode||13===e.keyCode&&e.shiftKey||(e.preventDefault(),o.current.dispatchEvent(new Event("submit")))},autoFocus:!0})))},it=function(){var e=window.Drupal&&window.Drupal.settings&&window.Drupal.settings.consultantId?window.Drupal.settings.consultantId.toString():"1",t=Object(a.useContext)(y),n=Object(i.a)(t,2),s=n[0],c=n[1];return r.a.createElement(b.c,{query:h,fetchPolicy:"network-only",variables:{questionId:s.backendChat.questionId}},function(t){var n=t.data,a=t.loading,s=t.subscribeToMore;return n&&n.question&&!a?("complete"===n.question.status&&c({type:"RESET_CHAT",payload:null}),r.a.createElement("div",{className:"backend-chat"},r.a.createElement(Pe,{name:n.question.authorName,email:n.question.authorEmail,source:n.question.source}),r.a.createElement(Ge,{lastHeartbeat:n.question.lastHeartbeatAt}),n.question.consultant!==e&&r.a.createElement(Je,null),r.a.createElement(Xe,{author:n.question.authorName,subject:n.question.subject,questionCreatedAt:n.question.createdAt,messages:n.question.messages,subscribeToMore:s}),n.question.consultant===e&&r.a.createElement(ct,null),n.question.consultant===e&&r.a.createElement(b.b,{mutation:O},function(e){return r.a.createElement(ut,{createMessage:e})}))):""})},ot=function(){var e=Object(a.useContext)(y),t=Object(i.a)(e,1)[0].backendChat?r.a.createElement(it,null):"";return r.a.createElement(a.Fragment,null,r.a.createElement(Be,null),t)},lt=function(e){var t=e.children;return r.a.createElement(rt,null,r.a.createElement(S,null,t))},dt=function(e){var t=e.children,n=e.data,r=e.loading,s=Object(a.useContext)(nt),c=Object(i.a)(s,2)[1];return Object(a.useEffect)(function(){n&&!r&&c({type:"SET_SETTINGS",payload:n.settings})},[]),t},mt=function(e){var t=e.children;return r.a.createElement(b.c,{query:ge},function(e){var n=e.data,a=e.loading;return!n||a?t:r.a.createElement(dt,{data:n,loading:a},t)})},bt=function(){return r.a.createElement(fe,null,r.a.createElement(lt,null,r.a.createElement(mt,null,r.a.createElement(ot,null))))};""!==u("renderOnly")?("backend"===u("renderOnly")&&document.getElementById("chatty_backend")&&c.a.render(r.a.createElement(bt,null),document.getElementById("chatty_backend")),"client"===u("renderOnly")&&document.getElementById("chatty_client")&&c.a.render(r.a.createElement(qe,null),document.getElementById("chatty_client"))):(document.getElementById("chatty_client")&&c.a.render(r.a.createElement(qe,null),document.getElementById("chatty_client")),document.getElementById("chatty_backend")&&c.a.render(r.a.createElement(bt,null),document.getElementById("chatty_backend")))}},[[214,1,2]]]);
//# sourceMappingURL=main.893517e5.chunk.js.map