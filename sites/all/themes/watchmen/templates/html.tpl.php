<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 *
 * @ingroup themeable
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>

<head profile="<?php print $grddl_profile; ?>">
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
  <div id="skip-link">
    <a href="#main-content" class="element-invisible element-focusable"><?php print t('Skip to main content'); ?></a>
  </div>

  <?php print $page_top; ?>
  <?php print $page; ?>

  <?php if ($user->uid !== 0): ?>
    <!-- Begin - chatty -->
    <div id="chatty_backend"></div>
    <!-- End - chatty -->

    <!-- Begin - colleague chat -->
    <div class="colleague-chat" data-name="<?=$colleague_chat['users_name']; ?>">
      <div class="colleague-chat__heading">
        <span class="colleague-chat__message-status"></span>

        <h4 class="colleague-chat__heading__title"><?=t('Kollega chat'); ?></h4>
      </div>

      <div class="colleague-chat__members">
        <div class="colleague-chat__members-count">-</div>
        <div class="colleague-chat__members-list">-</div>
      </div>

      <div class="colleague-chat__content">
        <div class="colleague-chat__messages"></div>
      </div>

      <form class="colleague-chat__form" onsubmit="return false;">
        <input class="colleague-chat__form__input" placeholder="<?=t('Skriv en besked...'); ?>" type="text"/>
        <input class="colleague-chat__form__submit" value="Send" type="submit"/>
      </form>

    </div>
    <!-- End - colleague chat -->
  <?php endif; ?>

  <!-- Begin - load javascript files -->
  <script>!function (l) {
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
    }([])</script>

  <?php print $scripts; ?>
  <!-- End - load javascript files -->

  <?php print $page_bottom; ?>
</body>
</html>
