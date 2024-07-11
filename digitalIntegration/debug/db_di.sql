/*
 Navicat Premium Data Transfer

 Source Server         : jh_database
 Source Server Type    : MySQL
 Source Server Version : 80200
 Source Host           : localhost:3306
 Source Schema         : db_di

 Target Server Type    : MySQL
 Target Server Version : 80200
 File Encoding         : 65001

 Date: 10/07/2024 10:34:49
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_data_approval
-- ----------------------------
DROP TABLE IF EXISTS `t_data_approval`;
CREATE TABLE `t_data_approval`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `proposer` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `department` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `applicationTime` datetime(0) NULL DEFAULT NULL,
  `host` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `createTime` datetime(0) NULL DEFAULT NULL,
  `tool` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `fileName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `fileType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `state` int NULL DEFAULT NULL COMMENT '审批 0:未审批 1：审批同意，2审批驳回 ',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 23 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_data_approval
-- ----------------------------
INSERT INTO `t_data_approval` VALUES (1, '1', '1', '2024-07-05 16:49:39', '刀片机1', '2024-07-05 16:49:39', 'Mentor', 'Mentor', 'txt', 1);
INSERT INTO `t_data_approval` VALUES (2, '1', '1', '2024-07-08 08:53:33', '刀片机1', '2024-07-08 08:53:33', 'Mentor', 'Mentor', 'txt', 2);
INSERT INTO `t_data_approval` VALUES (3, '1', '1', '2024-07-08 09:02:10', '刀片机1', '2024-07-08 09:02:10', 'Mentor', 'Mentor', 'txt', 1);
INSERT INTO `t_data_approval` VALUES (4, '1', '1', '2024-07-08 10:52:33', '刀片机1', '2024-07-08 10:52:33', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (5, '1', '1', '2024-07-08 10:52:35', '刀片机1', '2024-07-08 10:52:35', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (6, '1', '1', '2024-07-08 10:52:36', '刀片机1', '2024-07-08 10:52:36', 'Mentor', 'Mentor', 'txt', 1);
INSERT INTO `t_data_approval` VALUES (7, '1', '1', '2024-07-08 10:52:36', '刀片机1', '2024-07-08 10:52:36', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (8, '1', '1', '2024-07-08 10:52:36', '刀片机1', '2024-07-08 10:52:36', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (9, '1', '1', '2024-07-08 10:52:36', '刀片机1', '2024-07-08 10:52:36', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (10, '1', '1', '2024-07-08 10:52:37', '刀片机1', '2024-07-08 10:52:37', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (11, '1', '1', '2024-07-08 10:52:37', '刀片机1', '2024-07-08 10:52:37', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (12, '1', '1', '2024-07-08 10:52:37', '刀片机1', '2024-07-08 10:52:37', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (13, '1', '1', '2024-07-08 10:52:37', '刀片机1', '2024-07-08 10:52:37', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (14, '1', '1', '2024-07-08 10:52:37', '刀片机1', '2024-07-08 10:52:37', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (15, '1', '1', '2024-07-08 10:52:37', '刀片机1', '2024-07-08 10:52:37', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (16, '1', '1', '2024-07-08 10:52:38', '刀片机1', '2024-07-08 10:52:38', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (17, '1', '1', '2024-07-08 10:52:38', '刀片机1', '2024-07-08 10:52:38', 'Mentor', 'Mentor', 'txt', 2);
INSERT INTO `t_data_approval` VALUES (18, '1', '1', '2024-07-08 10:52:38', '刀片机1', '2024-07-08 10:52:38', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (19, '1', '1', '2024-07-08 10:52:38', '刀片机1', '2024-07-08 10:52:38', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (20, '1', '1', '2024-07-08 10:52:38', '刀片机1', '2024-07-08 10:52:38', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (21, '1', '1', '2024-07-08 10:52:38', '刀片机1', '2024-07-08 10:52:38', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (22, '1', '1', '2024-07-08 10:52:39', '刀片机1', '2024-07-08 10:52:39', 'Mentor', 'Mentor', 'txt', 0);

-- ----------------------------
-- Table structure for t_ip
-- ----------------------------
DROP TABLE IF EXISTS `t_ip`;
CREATE TABLE `t_ip`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `host` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `ip` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `module` int NULL DEFAULT NULL COMMENT '模块\r\n',
  `used` int NULL DEFAULT NULL COMMENT 'IP是否使用 1：已使用 0：未使用',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 8 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_ip
-- ----------------------------
INSERT INTO `t_ip` VALUES (2, '11', '192.168.0.1', 1, 1);
INSERT INTO `t_ip` VALUES (3, 'host', '', 4, 0);
INSERT INTO `t_ip` VALUES (4, 'host4', '192.168.10.1', 4, 0);
INSERT INTO `t_ip` VALUES (5, 'host3', '192.168.3.1', 3, 0);
INSERT INTO `t_ip` VALUES (7, 'host2', '192.168.2.2', 2, 0);

-- ----------------------------
-- Table structure for t_tools
-- ----------------------------
DROP TABLE IF EXISTS `t_tools`;
CREATE TABLE `t_tools`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '主键字',
  `name` varchar(50) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '软件名',
  `host` varchar(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '主机名',
  `path` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '路径\r\n',
  `icoPath` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '图标路径',
  `module` int NOT NULL COMMENT '模块',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_PKID`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 195 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_tools
-- ----------------------------
INSERT INTO `t_tools` VALUES (169, 'ps', 'host2', 'd:', 'd:', 2);
INSERT INTO `t_tools` VALUES (170, 'AE', 'host2', 'D', 'D', 2);
INSERT INTO `t_tools` VALUES (171, 'PS', 'hots3', 'D', 'E', 3);
INSERT INTO `t_tools` VALUES (172, 'AR', 'host4', 'E', 'E:', 4);
INSERT INTO `t_tools` VALUES (173, 'AD', '1', '1', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\adobe_xd.png', 1);
INSERT INTO `t_tools` VALUES (182, 'DI', 'host1', 'D', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 2);
INSERT INTO `t_tools` VALUES (183, 'CE', 'host2', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'D', 2);
INSERT INTO `t_tools` VALUES (185, 'DI', 'host3', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'E', 3);
INSERT INTO `t_tools` VALUES (186, 'DI', 'host3', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'E', 3);
INSERT INTO `t_tools` VALUES (189, 'CD', 'VD', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\icon.ico', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\icon.ico', 2);
INSERT INTO `t_tools` VALUES (190, 'QQ', 'host1', 'D:\\tools\\QQ\\Bin\\QQ.exe', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\QQ.png', 1);
INSERT INTO `t_tools` VALUES (191, 'EV录屏', 'host1', 'D:\\tools\\EVCapture\\EVCapture.exe', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\EV.ico', 1);
INSERT INTO `t_tools` VALUES (194, '1', 'host2', '1', '1', 2);

-- ----------------------------
-- Table structure for t_user
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user`  (
  `PKID` int NOT NULL AUTO_INCREMENT,
  `UserName` varchar(20) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '用户名',
  `Password` varchar(20) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '密码',
  `name` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL DEFAULT NULL,
  `department` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL DEFAULT NULL,
  `JobTitle` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL DEFAULT NULL,
  `PhoneNumber` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL DEFAULT NULL,
  `Pop` varchar(10) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '身份，0：管理员，1：普通用户\r\n',
  `CreateTime` datetime(0) NOT NULL COMMENT '创建用户时间',
  `approval` varchar(50) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NULL DEFAULT '' COMMENT '审批 0:未审批 1：审批同意，2审批驳回 ',
  PRIMARY KEY (`PKID`, `UserName`, `Password`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 105 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_user
-- ----------------------------
INSERT INTO `t_user` VALUES (68, '1', '1', '1', '1', '1', '1', '0', '2021-03-04 19:27:50', '1');
INSERT INTO `t_user` VALUES (80, '2', '2', '2', '', '', '', '0', '2024-06-21 09:52:01', '2');
INSERT INTO `t_user` VALUES (81, '2', '2', '2', '', '', '', '0', '2024-06-21 09:54:54', '2');
INSERT INTO `t_user` VALUES (82, '3', '3', '3', '3', '3', '3', '0', '2024-06-21 13:39:07', '2');
INSERT INTO `t_user` VALUES (83, '44', '3', '梁超群', '33', '3', '3', '0', '2024-06-24 10:14:08', '1');
INSERT INTO `t_user` VALUES (84, '21', '21', '21', '21', '21', '21', '0', '2024-06-24 10:41:30', '2');
INSERT INTO `t_user` VALUES (85, '22', '22', '22', '22', '22', '22', '0', '2024-06-24 10:41:39', '1');
INSERT INTO `t_user` VALUES (86, '23', '23', '23', '23', '23', '23', '0', '2024-06-24 10:41:49', '2');
INSERT INTO `t_user` VALUES (87, '31', '31', '31', '31', '', '31', '0', '2024-06-24 11:52:43', '1');
INSERT INTO `t_user` VALUES (88, '32', '32', '32', '32', '32', '32', '0', '2024-06-24 11:52:54', '1');
INSERT INTO `t_user` VALUES (89, '33', '33', '33', '33', '3', '', '0', '2024-06-24 11:53:03', '1');
INSERT INTO `t_user` VALUES (90, '34', '34', '34', '', '', '', '1', '2024-06-24 11:53:18', '1');
INSERT INTO `t_user` VALUES (91, '35', '35', '35', '', '', '', '1', '2024-06-24 11:53:28', '0');
INSERT INTO `t_user` VALUES (92, '41', '41', '41', '41', '41', '41', '0', '2024-06-24 17:31:47', '0');
INSERT INTO `t_user` VALUES (93, '42', '444', '42', '42', '42', '42', '1', '2024-06-24 17:31:59', '0');
INSERT INTO `t_user` VALUES (94, '43', '434', '43', '434', '43', '43', '1', '2024-06-24 17:32:13', '0');
INSERT INTO `t_user` VALUES (95, '45', '444', '44', '44', '44', '44', '1', '2024-06-24 17:32:30', '0');
INSERT INTO `t_user` VALUES (96, '46', '46', '46', '46', '46', '46', '1', '2024-06-24 17:32:48', '0');
INSERT INTO `t_user` VALUES (97, '47', '47', '47', '47', '47', '47', '1', '2024-06-24 17:33:01', '0');
INSERT INTO `t_user` VALUES (98, '48', '48', '48', '48', '48', '48', '0', '2024-06-24 17:33:09', '0');
INSERT INTO `t_user` VALUES (99, '49', '49', '49', '49', '49', '49', '0', '2024-06-24 17:33:21', '1');
INSERT INTO `t_user` VALUES (100, 'wz', '1', '1', '1', '1', '1', '0', '2024-07-03 14:54:47', '1');
INSERT INTO `t_user` VALUES (101, '110', '1', '110', '110', '110', '110', '1', '2024-07-03 15:14:53', '1');
INSERT INTO `t_user` VALUES (102, '111', '1', '111', '111', '111', '111', '1', '2024-07-03 15:18:08', '0');
INSERT INTO `t_user` VALUES (103, 'wxb', '1', '1', '1', '1', '1', '0', '2024-07-08 09:05:05', '1');
INSERT INTO `t_user` VALUES (104, 'ww', '1', '1', '1', '1', '1', '0', '2024-07-08 09:32:13', '1');

SET FOREIGN_KEY_CHECKS = 1;
