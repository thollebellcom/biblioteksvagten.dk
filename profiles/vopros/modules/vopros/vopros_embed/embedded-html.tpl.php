<?php

/**
 * @file
 * HTML for embedded pages.
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html lang="<?php print $language->language; ?>" xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>">

<head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
</head>
<body class="vopros-embed <?php print $classes; ?>" <?php print $attributes;?>>
  <?php print $page_top; ?>
  <?php print $page; ?>

  <!-- Begin - load javascript files -->
  <script>
    !function (l) {
      function e(e) {
        for (var r, t, n = e[0], o = e[1], u = e[2], f = 0, i = []; f < n.length; f++) {
          t = n[f], p[t] && i.push(p[t][0]), p[t] = 0;
        }
        for (r in o) {
          Object.prototype.hasOwnProperty.call(o, r) && (l[r] = o[r]);
        }
        for (s && s(e); i.length;) {
          i.shift()();
        }
        return c.push.apply(c, u || []), a()
      }

      function a() {
        for (var e, r = 0; r < c.length; r++) {
          for (var t = c[r], n = !0, o = 1; o < t.length; o++) {
            var u = t[o];
            0 !== p[u] && (n = !1)
          }
          n && (c.splice(r--, 1), e = f(f.s = t[0]))
        }
        return e
      }

      var t = {}, p = {1: 0}, c = [];

      function f(e) {
        if (t[e]) {
          return t[e].exports;
        }
        var r = t[e] = {i: e, l: !1, exports: {}};
        return l[e].call(r.exports, r, r.exports, f), r.l = !0, r.exports
      }

      f.m = l, f.c = t, f.d = function (e, r, t) {
        f.o(e, r) || Object.defineProperty(e, r, {enumerable: !0, get: t})
      }, f.r = function (e) {
        "undefined" != typeof Symbol && Symbol.toStringTag && Object.defineProperty(e, Symbol.toStringTag, {value: "Module"}), Object.defineProperty(e, "__esModule", {value: !0})
      }, f.t = function (r, e) {
        if (1 & e && (r = f(r)), 8 & e) {
          return r;
        }
        if (4 & e && "object" == typeof r && r && r.__esModule) {
          return r;
        }
        var t = Object.create(null);
        if (f.r(t), Object.defineProperty(t, "default", {
          enumerable: !0,
          value: r
        }), 2 & e && "string" != typeof r) {
          for (var n in r) {
            f.d(t, n, function (e) {
              return r[e]
            }.bind(null, n));
          }
        }
        return t
      }, f.n = function (e) {
        var r = e && e.__esModule ? function () {
          return e.default
        } : function () {
          return e
        };
        return f.d(r, "a", r), r
      }, f.o = function (e, r) {
        return Object.prototype.hasOwnProperty.call(e, r)
      }, f.p = "/";
      var r = window.webpackJsonp = window.webpackJsonp || [], n = r.push.bind(r);
      r.push = e, r = r.slice();
      for (var o = 0; o < r.length; o++) {
        e(r[o]);
      }
      var s = n;
      a()
    }([])
  </script>

  <?php print $scripts; ?>
  <!-- End - load javascript files -->

  <?php print $page_bottom; ?>
</body>
</html>
