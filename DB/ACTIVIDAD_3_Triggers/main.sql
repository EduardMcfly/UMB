# -------------------------------
# -- Table structure for categories
# -- ----------------------------
CREATE TABLE IF NOT EXISTS `blogs` (
  `id` INT AUTO_INCREMENT,
  `title` varchar(255),
  `content` varchar(255),
  `author` varchar(255),
  `date` DATE,
  `created_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `deleted_at` DATE,
  PRIMARY KEY (id)
);
# -------------------------------
# -- Table structure for notifications
# -- ----------------------------
CREATE TABLE IF NOT EXISTS `notifications` (
  `id` INT AUTO_INCREMENT,
  `blog_id` INT,
  `notification` varchar(255),
  `date` DATE,
  `created_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_at` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `deleted_at` DATE,
  PRIMARY KEY (id),
  FOREIGN KEY (`blog_id`) REFERENCES `blogs` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
);
# -------------------------------
# -- Trigger
# -- ----------------------------
CREATE TRIGGER insertNotification
AFTER
INSERT ON blogs FOR EACH ROW
INSERT INTO notifications (blog_id, date, notification)
VALUES
  (
    NEW.id,
    CURRENT_DATE,
    CONCAT(NEW.author, ' add the blog ', NEW.title)
  )