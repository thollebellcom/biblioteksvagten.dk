<?php
/**
 * @file
 * Display an embedded page.
 */
?>

<div id="embedded-page-wrapper"><div id="page">

  <div id="main-wrapper"><div id="main" class="clearfix">

    <div id="content">
      <div class="header">
        <?php if ($logo): ?>
        <!-- Logo -->
          <?php print $logo ?>
        <?php endif; ?>

        <?php print render($title_prefix); ?>
        <!-- Title -->
          <?php if ($title): ?>
            <h1 class="title" id="page-title"><?php print $title; ?></h1>
          <?php endif; ?>
        <?php print render($title_suffix); ?>
      </div> <!-- /.header -->

      <!-- Messages -->
      <?php print $messages; ?>

      <!-- Content -->
      <?php print render($page['content']); ?>
    </div> <!-- /#content -->

  </div></div> <!-- /#main, /#main-wrapper -->

  <div id="footer"><div class="section">
    <?php print render($page['footer']); ?>
  </div></div> <!-- /.section, /#footer -->

</div></div> <!-- /#page, /#page-wrapper -->
