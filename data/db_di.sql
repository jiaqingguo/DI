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

 Date: 05/11/2024 14:22:42
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_account_password
-- ----------------------------
DROP TABLE IF EXISTS `t_account_password`;
CREATE TABLE `t_account_password`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `account` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `used` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_account_password
-- ----------------------------
INSERT INTO `t_account_password` VALUES (1, 'user', '123456', 0);

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
) ENGINE = InnoDB AUTO_INCREMENT = 38 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_data_approval
-- ----------------------------
INSERT INTO `t_data_approval` VALUES (1, '1', '1', '2024-07-05 16:49:39', '刀片机1', '2024-07-05 16:49:39', 'Mentor', 'Mentor', 'txt', 1);
INSERT INTO `t_data_approval` VALUES (2, '1', '1', '2024-07-08 08:53:33', '刀片机1', '2024-07-08 08:53:33', 'Mentor', 'Mentor', 'txt', 2);
INSERT INTO `t_data_approval` VALUES (3, '1', '1', '2024-07-08 09:02:10', '刀片机1', '2024-07-08 09:02:10', 'Mentor', 'Mentor', 'txt', 1);
INSERT INTO `t_data_approval` VALUES (4, '1', '1', '2024-07-08 10:52:33', '刀片机1', '2024-07-08 10:52:33', 'Mentor', 'Mentor', 'txt', 1);
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
INSERT INTO `t_data_approval` VALUES (23, '1', '1', '2024-07-11 09:06:15', '刀片机1', '2024-07-11 09:06:15', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (24, '1', '1', '2024-07-12 09:12:24', '刀片机1', '2024-07-12 09:12:24', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (25, '1', '1', '2024-07-12 09:12:25', '刀片机1', '2024-07-12 09:12:25', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (26, '1', '1', '2024-07-12 09:12:26', '刀片机1', '2024-07-12 09:12:26', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (27, '1', '1', '2024-07-12 09:12:26', '刀片机1', '2024-07-12 09:12:26', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (28, '1', '1', '2024-07-12 09:12:26', '刀片机1', '2024-07-12 09:12:26', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (29, '1', '1', '2024-07-12 09:12:26', '刀片机1', '2024-07-12 09:12:26', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (30, '1', '1', '2024-07-12 09:12:29', '刀片机1', '2024-07-12 09:12:29', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (31, '1', '1', '2024-07-12 09:12:32', '刀片机1', '2024-07-12 09:12:32', 'Mentor', 'Mentor', 'txt', 1);
INSERT INTO `t_data_approval` VALUES (32, '1', '1', '2024-07-12 09:12:53', '刀片机1', '2024-07-12 09:12:53', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (33, '1', '1', '2024-07-12 10:11:02', '刀片机1', '2024-07-12 10:11:02', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (34, '1', '1', '2024-07-22 14:22:10', '刀片机1', '2024-07-22 14:22:10', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (35, '1', '1', '2024-07-22 14:40:17', '刀片机1', '2024-07-22 14:40:17', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (36, '1', '1', '2024-07-22 14:58:36', '刀片机1', '2024-07-22 14:58:36', 'Mentor', 'Mentor', 'txt', 0);
INSERT INTO `t_data_approval` VALUES (37, '1', '1', '2024-07-22 15:02:49', '刀片机1', '2024-07-22 15:02:49', 'Mentor', 'Mentor', 'txt', 0);

-- ----------------------------
-- Table structure for t_download_approval
-- ----------------------------
DROP TABLE IF EXISTS `t_download_approval`;
CREATE TABLE `t_download_approval`  (
  `id` int UNSIGNED NOT NULL AUTO_INCREMENT,
  `userID` int NULL DEFAULT NULL,
  `applicationTime` datetime(0) NULL DEFAULT NULL,
  `filePath` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `fileType` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `fileTime` datetime(0) NULL DEFAULT NULL COMMENT '文件生成时间',
  `status` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '审批状态 0 未审批 1：审批通过 2：驳回审批；',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 24 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_download_approval
-- ----------------------------

-- ----------------------------
-- Table structure for t_fingerprint
-- ----------------------------
DROP TABLE IF EXISTS `t_fingerprint`;
CREATE TABLE `t_fingerprint`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `fingerData` varchar(5000) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '指纹',
  `fingerLen` int NULL DEFAULT NULL,
  `registUserid` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 79 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_fingerprint
-- ----------------------------
INSERT INTO `t_fingerprint` VALUES (78, 'TQ1TUzIxAAAETkwECAUHCc7QAAAoT5EBAABahPMlaU7dAABkdwA4AHYqiAD9AIxkZwDNThZkOAD9ABxkl06PAApkXgC7AHUqPwCEAO9kGgCvTpIMXwBpADlkME5xAGNkfQCLAPoq+QB3AKUeQwDiTh1kVQDnAJxke04JAStkcQDRAUV/NQAIAVFk/QAeT9BYxACaANZkF04FAVxSKwD/AVQX0ACNAI5hiwBkT68xpQBNAMBgj07aAIFkaAA7APwqZQAGAU1kdQACTzBeQQCfAClkcE6FAHNk1ADJASgIzAAoATQ6QQBST69kMgBIAf8woU5hAalQKwCiAQEH8KuR54KA8EiJMhDpVWB1HXRy1dXL/t8a9IssC4rPB5iD+QeaFHUdTIuEQY7NB0+Ags6fBMPzyY1viW5MTHYaay73R/riSMqOShsvF4KXMNGgkvUfFVuLYFJD/Lg1oLnt4BnluwjS/HtpgXP0bc9w+wKBTYVDgP9HKwwehj6PmBgGz3NPVX0i/BvrSudzdXdh/goO/9/ZUWflb36AGa6Bxri6CFZVDeTdUkvbpnb/Uf+3f0/GmAYaaLZ5ZPvas96jGQvyB2KP5ktOAotv9exXNGLDZ/2zd1v/g8xyFz+3/VqvzcogPU8DbyEPCwBgL3OxwXvAgA0Adzd+FmyDSg8AvYSDdCNuZMEGAICI9/qPMgQAqE0MmwoENlB6fsHAfMwAhBwBOMIyDQCnZ/N2TTXB/AoAn2t0j8JZUQ4AYqn9xHM8/1L5BQD2cmOMVQQA/Hk0hwkEKn39wD3+WdUARM/oKf9PR/4FwPtEAV2BcMHBB2RdQgFzgnd3f5P/Dk56gwA9TifAAHfGdXgHADuJp8FcjxYA+IuwxrfCb4/AhIZiRAjFlohIQ/4sDgCOSIOXjsGJUv8IAFORC48ucAgAo8zSPUBYAejEmmpyB8DAj3DCZMBbF9UEBZBlwTYwwP32/2QIEQBZ5OT+O/v5sTk4WAwAiiIX+mDBwf94CBAXX617w2YFAFHpmcGBSwFV61rCZdIA45OjwXvCesEGwcWPeVxDEwA4P9b7dS3AKEvBQtYAObLW//8u/vsF/vuxwf/9wf/BxgBtsvH4GADn6WHBxT6FkXfC/8GsLw5eZQNcxIzDBMDGRhGBCSkywpkHFH4LUP9T/wPVZA8ewhkA7PynBMDFjf/ChJGDeKBBAV40DEz+XAjVcwpe98L+wZMD1dUUZf4JEHcTN6J1+1QR7AupaoQGTsEiw8DAw/7BBf/7jgkQbhZJnVYGFD0XQ5bAFRD7J8sJ/v/6/cD9PsH7sf/A/cHAwcEQyWI2bQYQWzT1wJRKET84NIUD1TtGesMDEDZLNAEaFIdopP7APsG/wseKr/+SwsJp0RC1Lar/wv3/wAfCzIjHw8HEwoA6FxTyZKc+/3LCY8TGjMDDwYnCUocAHQ0AAgEAeAHfPARMATYBXEQAxRlBHA==', 1102, 324);

-- ----------------------------
-- Table structure for t_ip
-- ----------------------------
DROP TABLE IF EXISTS `t_ip`;
CREATE TABLE `t_ip`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `ip` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `host` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `software` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `module` int NULL DEFAULT NULL COMMENT '模块\r\n',
  `used` int NULL DEFAULT NULL COMMENT 'IP是否使用 1：已使用 0：未使用',
  `userName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `iconPath` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `number` int NULL DEFAULT NULL,
  `toolPath` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 1107 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_ip
-- ----------------------------
INSERT INTO `t_ip` VALUES (413, '192.168.1.251', '节点1', 'A', 1, 0, '300', '0', 1, 'C:\\\\Program Files (网易)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (414, '192.168.0.1', '节点1', 'B', 1, 0, '300', '0', 1, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (415, '192.168.0.2', '节点2', 'D', 1, 0, '300', '0', 1, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (416, '192.168.0.3', '硬件加速机1', 'C', 1, 0, '300', '0', 1, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (417, '192.168.0.4', '节点1', 'A', 1, 0, '4', '0', 4, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (418, '192.168.0.4', '节点1', 'B', 1, 0, '4', '0', 4, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (419, '192.168.0.5', '节点2', 'D', 1, 0, '4', '0', 4, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (420, '192.168.0.6', '硬件加速机1', 'C', 1, 0, '4', '0', 4, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (421, '192.168.10.1', '节点3', 'A', 1, 0, '299', '0', 2, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (422, '192.168.10.1', '节点3', 'B', 1, 0, '299', '0', 2, 'c：debug\\\\网易');
INSERT INTO `t_ip` VALUES (423, '192.168.10.2', '节点4', 'D', 1, 0, '299', '0', 2, 'c：debug');
INSERT INTO `t_ip` VALUES (424, '192.168.10.3', '硬件加速机2', 'C', 1, 0, '299', '0', 2, 'c：debug');
INSERT INTO `t_ip` VALUES (425, '192.168.10.4', '节点3', 'A', 1, 0, '5', '0', 5, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (426, '192.168.10.4', '节点3', 'B', 1, 0, '5', '0', 5, 'c：debug');
INSERT INTO `t_ip` VALUES (427, '192.168.10.5', '节点4', 'D', 1, 0, '5', '0', 5, 'c：debug');
INSERT INTO `t_ip` VALUES (428, '192.168.10.6', '硬件加速机2', 'C', 1, 0, '5', '0', 5, 'c：debug');
INSERT INTO `t_ip` VALUES (429, '192.168.100.1', '节点5', 'A', 1, 0, '298', '0', 3, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (430, '192.168.100.1', '节点5', 'B', 1, 0, '298', '0', 3, 'c：debug');
INSERT INTO `t_ip` VALUES (431, '192.168.100.2', '节点6', 'D', 1, 0, '298', '0', 3, 'c：debug');
INSERT INTO `t_ip` VALUES (432, '192.168.100.3', '硬件加速机3', 'C', 1, 0, '298', '0', 3, 'c：debug');
INSERT INTO `t_ip` VALUES (433, '192.168.100.4', '节点5', 'A', 1, 0, '6', '0', 6, 'C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2017\\\\Enterprise\\\\Common7\\\\IDE\\\\devenv.exe');
INSERT INTO `t_ip` VALUES (434, '192.168.100.4', '节点5', 'B', 1, 0, '6', '0', 6, 'c：debug');
INSERT INTO `t_ip` VALUES (435, '192.168.100.5', '节点6', 'D', 1, 0, '6', '0', 6, 'c：debug');
INSERT INTO `t_ip` VALUES (436, '192.168.100.6', '硬件加速机3', 'C', 1, 0, '6', '0', 6, 'c：debug');
INSERT INTO `t_ip` VALUES (974, '192.168.0.1', '节点1', '夸克', 4, 0, '299', 'D：////', 1, '');
INSERT INTO `t_ip` VALUES (975, '192.168.0.2', '节点2', '夸克', 4, 0, '299', 'D：////', 1, '');
INSERT INTO `t_ip` VALUES (976, '192.168.0.3', '加速机1', '夸克', 4, 0, '299', 'D：////', 1, '');
INSERT INTO `t_ip` VALUES (977, '192.168.0.4', '节点1', '夸克', 4, 0, '299', 'D：////', 4, '');
INSERT INTO `t_ip` VALUES (978, '192.168.0.5', '节点2', '夸克', 4, 0, '299', 'D：////', 4, '');
INSERT INTO `t_ip` VALUES (979, '192.168.0.6', '加速机1', '夸克', 4, 0, '299', 'D：////', 4, '');
INSERT INTO `t_ip` VALUES (980, '192.168.10.1', '节点3', '夸克', 4, 0, '299', 'D：////', 2, '');
INSERT INTO `t_ip` VALUES (981, '192.168.10.2', '节点4', '夸克', 4, 0, '299', 'D：////', 2, '');
INSERT INTO `t_ip` VALUES (982, '192.168.10.3', '加速机2', '夸克', 4, 0, '299', 'D：////', 2, '');
INSERT INTO `t_ip` VALUES (983, '192.168.10.4', '节点3', '夸克', 4, 0, '299', 'D：////', 5, '');
INSERT INTO `t_ip` VALUES (984, '192.168.10.5', '节点4', '夸克', 4, 0, '299', 'D：////', 5, '');
INSERT INTO `t_ip` VALUES (985, '192.168.10.6', '加速机2', '夸克', 4, 0, '299', 'D：////', 5, '');
INSERT INTO `t_ip` VALUES (986, '192.168.100.1', '节点5', '夸克', 4, 0, '299', 'D：////', 3, '');
INSERT INTO `t_ip` VALUES (987, '192.168.100.2', '节点6', '夸克', 4, 0, '299', 'D：////', 3, '');
INSERT INTO `t_ip` VALUES (988, '192.168.100.3', '加速机3', '夸克', 4, 0, '299', 'D：////', 3, '');
INSERT INTO `t_ip` VALUES (989, '192.168.100.4', '节点5', '夸克', 4, 0, '299', 'D：////', 6, '');
INSERT INTO `t_ip` VALUES (990, '192.168.100.5', '节点6', '夸克', 4, 0, '299', 'D：////', 6, '');
INSERT INTO `t_ip` VALUES (991, '192.168.100.6', '加速机3', '夸克', 4, 0, '299', 'D：////', 6, '');
INSERT INTO `t_ip` VALUES (992, '192.168.0.1', '节点1', '迅雷', 2, 0, '299', 'D://', 1, '');
INSERT INTO `t_ip` VALUES (993, '192.168.0.2', '节点2', '迅雷', 2, 0, '299', 'D://', 1, '');
INSERT INTO `t_ip` VALUES (994, '192.168.0.3', '加速机1', '迅雷', 2, 0, '299', 'D://', 1, '');
INSERT INTO `t_ip` VALUES (995, '192.168.0.4', '节点1', '迅雷', 2, 0, '299', 'D://', 4, '');
INSERT INTO `t_ip` VALUES (996, '192.168.0.5', '节点2', '迅雷', 2, 0, '299', 'D://', 4, '');
INSERT INTO `t_ip` VALUES (997, '192.168.0.6', '加速机1', '迅雷', 2, 0, '299', 'D://', 4, '');
INSERT INTO `t_ip` VALUES (998, '192.168.10.1', '节点3', '迅雷', 2, 0, '299', 'D://', 2, '');
INSERT INTO `t_ip` VALUES (999, '192.168.10.2', '节点4', '迅雷', 2, 0, '299', 'D://', 2, '');
INSERT INTO `t_ip` VALUES (1000, '192.168.10.3', '加速机2', '迅雷', 2, 0, '299', 'D://', 2, '');
INSERT INTO `t_ip` VALUES (1001, '192.168.10.4', '节点3', '迅雷', 2, 0, '299', 'D://', 5, '');
INSERT INTO `t_ip` VALUES (1002, '192.168.10.5', '节点4', '迅雷', 2, 0, '299', 'D://', 5, '');
INSERT INTO `t_ip` VALUES (1003, '192.168.10.6', '加速机2', '迅雷', 2, 0, '299', 'D://', 5, '');
INSERT INTO `t_ip` VALUES (1004, '192.168.100.1', '节点5', '迅雷', 2, 0, '299', 'D://', 3, '');
INSERT INTO `t_ip` VALUES (1005, '192.168.100.2', '节点6', '迅雷', 2, 0, '299', 'D://', 3, '');
INSERT INTO `t_ip` VALUES (1006, '192.168.100.3', '加速机3', '迅雷', 2, 0, '299', 'D://', 3, '');
INSERT INTO `t_ip` VALUES (1007, '192.168.100.4', '节点5', '迅雷', 2, 0, '299', 'D://', 6, '');
INSERT INTO `t_ip` VALUES (1008, '192.168.100.5', '节点6', '迅雷', 2, 0, '299', 'D://', 6, '');
INSERT INTO `t_ip` VALUES (1009, '192.168.100.6', '加速机3', '迅雷', 2, 0, '299', 'D://', 6, '');
INSERT INTO `t_ip` VALUES (1053, '192.168.0.1', '节点1', '百度网盘', 3, 0, '299', 'F：/', 1, '');
INSERT INTO `t_ip` VALUES (1054, '192.168.0.2', '节点2', '百度网盘', 3, 0, '299', 'F：/', 1, '');
INSERT INTO `t_ip` VALUES (1055, '192.168.0.3', '加速机1', '百度网盘', 3, 0, '299', 'F：/', 1, '');
INSERT INTO `t_ip` VALUES (1056, '192.168.0.4', '节点1', '百度网盘', 3, 0, '299', 'F：/', 4, '');
INSERT INTO `t_ip` VALUES (1057, '192.168.0.5', '节点2', '百度网盘', 3, 0, '299', 'F：/', 4, '');
INSERT INTO `t_ip` VALUES (1058, '192.168.0.6', '加速机1', '百度网盘', 3, 0, '299', 'F：/', 4, '');
INSERT INTO `t_ip` VALUES (1059, '192.168.10.1', '节点3', '百度网盘', 3, 0, '299', 'F：/', 2, '');
INSERT INTO `t_ip` VALUES (1060, '192.168.10.2', '节点4', '百度网盘', 3, 0, '299', 'F：/', 2, '');
INSERT INTO `t_ip` VALUES (1061, '192.168.10.3', '加速机2', '百度网盘', 3, 0, '299', 'F：/', 2, '');
INSERT INTO `t_ip` VALUES (1062, '192.168.10.4', '节点3', '百度网盘', 3, 0, '299', 'F：/', 5, '');
INSERT INTO `t_ip` VALUES (1063, '192.168.10.5', '节点4', '百度网盘', 3, 0, '299', 'F：/', 5, '');
INSERT INTO `t_ip` VALUES (1064, '192.168.10.6', '加速机2', '百度网盘', 3, 0, '299', 'F：/', 5, '');
INSERT INTO `t_ip` VALUES (1065, '192.168.100.1', '节点5', '百度网盘', 3, 0, '299', 'F：/', 3, '');
INSERT INTO `t_ip` VALUES (1066, '192.168.100.2', '节点6', '百度网盘', 3, 0, '299', 'F：/', 3, '');
INSERT INTO `t_ip` VALUES (1067, '192.168.100.3', '加速机3', '百度网盘', 3, 0, '299', 'F：/', 3, '');
INSERT INTO `t_ip` VALUES (1068, '192.168.100.4', '节点5', '百度网盘', 3, 0, '299', 'F：/', 6, '');
INSERT INTO `t_ip` VALUES (1069, '192.168.100.5', '节点6', '百度网盘', 3, 0, '299', 'F：/', 6, '');
INSERT INTO `t_ip` VALUES (1070, '192.168.100.6', '加速机3', '百度网盘', 3, 0, '299', 'F：/', 6, '');
INSERT INTO `t_ip` VALUES (1071, '192.168.0.1', '节点1', '百度', 1, 0, '299', 'D：/debug', 1, '');
INSERT INTO `t_ip` VALUES (1072, '192.168.0.4', '节点1', '百度', 1, 0, '299', 'D：/debug', 4, '');
INSERT INTO `t_ip` VALUES (1073, '192.168.10.1', '节点3', '百度', 1, 0, '299', 'D：/debug', 2, '');
INSERT INTO `t_ip` VALUES (1074, '192.168.10.4', '节点3', '百度', 1, 0, '299', 'D：/debug', 5, '');
INSERT INTO `t_ip` VALUES (1075, '192.168.100.1', '节点5', '百度', 1, 0, '299', 'D：/debug', 3, '');
INSERT INTO `t_ip` VALUES (1076, '192.168.100.4', '节点5', '百度', 1, 0, '299', 'D：/debug', 6, '');
INSERT INTO `t_ip` VALUES (1077, '', '', 'A', 1, 0, '68', '11', 0, '');
INSERT INTO `t_ip` VALUES (1078, '', '', 'A', 1, 0, '68', '11', 0, '');
INSERT INTO `t_ip` VALUES (1079, '', '', 'A', 1, 0, '68', '11', 0, '');
INSERT INTO `t_ip` VALUES (1080, '', '', 'A', 1, 0, '68', '11', 0, '');
INSERT INTO `t_ip` VALUES (1081, '', '', 'A', 1, 0, '68', '11', 0, '');
INSERT INTO `t_ip` VALUES (1082, '', '', 'A', 1, 0, '68', '11', 0, '');
INSERT INTO `t_ip` VALUES (1083, '', '', 'EEEE', 1, 0, '68', '111', 0, '');
INSERT INTO `t_ip` VALUES (1084, '', '', 'EEEE', 1, 0, '68', '111', 0, '');
INSERT INTO `t_ip` VALUES (1085, '', '', 'EEEE', 1, 0, '68', '111', 0, '');
INSERT INTO `t_ip` VALUES (1086, '', '', 'EEEE', 1, 0, '68', '111', 0, '');
INSERT INTO `t_ip` VALUES (1087, '', '', 'EEEE', 1, 0, '68', '111', 0, '');
INSERT INTO `t_ip` VALUES (1088, '', '', 'EEEE', 1, 0, '68', '111', 0, '');
INSERT INTO `t_ip` VALUES (1089, '192.168.0.1', '节点1', '夸克', 4, 0, '283', 'C：/', 1, '');
INSERT INTO `t_ip` VALUES (1090, '192.168.0.2', '节点2', '夸克', 4, 0, '283', 'C：/', 1, '');
INSERT INTO `t_ip` VALUES (1091, '192.168.0.3', '加速机1', '夸克', 4, 0, '283', 'C：/', 1, '');
INSERT INTO `t_ip` VALUES (1092, '192.168.0.4', '节点1', '夸克', 4, 0, '283', 'C：/', 4, '');
INSERT INTO `t_ip` VALUES (1093, '192.168.0.5', '节点2', '夸克', 4, 0, '283', 'C：/', 4, '');
INSERT INTO `t_ip` VALUES (1094, '192.168.0.6', '加速机1', '夸克', 4, 0, '283', 'C：/', 4, '');
INSERT INTO `t_ip` VALUES (1095, '192.168.10.1', '节点3', '夸克', 4, 0, '283', 'C：/', 2, '');
INSERT INTO `t_ip` VALUES (1096, '192.168.10.2', '节点4', '夸克', 4, 0, '283', 'C：/', 2, '');
INSERT INTO `t_ip` VALUES (1097, '192.168.10.3', '加速机2', '夸克', 4, 0, '283', 'C：/', 2, '');
INSERT INTO `t_ip` VALUES (1098, '192.168.10.4', '节点3', '夸克', 4, 0, '283', 'C：/', 5, '');
INSERT INTO `t_ip` VALUES (1099, '192.168.10.5', '节点4', '夸克', 4, 0, '283', 'C：/', 5, '');
INSERT INTO `t_ip` VALUES (1100, '192.168.10.6', '加速机2', '夸克', 4, 0, '283', 'C：/', 5, '');
INSERT INTO `t_ip` VALUES (1101, '192.168.100.1', '节点5', '夸克', 4, 0, '283', 'C：/', 3, '');
INSERT INTO `t_ip` VALUES (1102, '192.168.100.2', '节点6', '夸克', 4, 0, '283', 'C：/', 3, '');
INSERT INTO `t_ip` VALUES (1103, '192.168.100.3', '加速机3', '夸克', 4, 0, '283', 'C：/', 3, '');
INSERT INTO `t_ip` VALUES (1104, '192.168.100.4', '节点5', '夸克', 4, 0, '283', 'C：/', 6, '');
INSERT INTO `t_ip` VALUES (1105, '192.168.100.5', '节点6', '夸克', 4, 0, '283', 'C：/', 6, '');
INSERT INTO `t_ip` VALUES (1106, '192.168.100.6', '加速机3', '夸克', 4, 0, '283', 'C：/', 6, '');

-- ----------------------------
-- Table structure for t_ip_configure
-- ----------------------------
DROP TABLE IF EXISTS `t_ip_configure`;
CREATE TABLE `t_ip_configure`  (
  `id` int NOT NULL,
  `ip` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `hostName` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `number` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_ip_configure
-- ----------------------------
INSERT INTO `t_ip_configure` VALUES (1, '192.168.0.1', '节点1', 1);
INSERT INTO `t_ip_configure` VALUES (2, '192.168.0.2', '节点2', 1);
INSERT INTO `t_ip_configure` VALUES (3, '192.168.0.3', '加速机1', 1);
INSERT INTO `t_ip_configure` VALUES (4, '192.168.0.4', '节点1', 4);
INSERT INTO `t_ip_configure` VALUES (5, '192.168.0.5', '节点2', 4);
INSERT INTO `t_ip_configure` VALUES (6, '192.168.0.6', '加速机1', 4);
INSERT INTO `t_ip_configure` VALUES (7, '192.168.10.1', '节点3', 2);
INSERT INTO `t_ip_configure` VALUES (8, '192.168.10.2', '节点4', 2);
INSERT INTO `t_ip_configure` VALUES (9, '192.168.10.3', '加速机2', 2);
INSERT INTO `t_ip_configure` VALUES (10, '192.168.10.4', '节点3', 5);
INSERT INTO `t_ip_configure` VALUES (11, '192.168.10.5', '节点4', 5);
INSERT INTO `t_ip_configure` VALUES (12, '192.168.10.6', '加速机2', 5);
INSERT INTO `t_ip_configure` VALUES (13, '192.168.100.1', '节点5', 3);
INSERT INTO `t_ip_configure` VALUES (14, '192.168.100.2', '节点6', 3);
INSERT INTO `t_ip_configure` VALUES (15, '192.168.100.3', '加速机3', 3);
INSERT INTO `t_ip_configure` VALUES (16, '192.168.100.4', '节点5', 6);
INSERT INTO `t_ip_configure` VALUES (17, '192.168.100.5', '节点6', 6);
INSERT INTO `t_ip_configure` VALUES (18, '192.168.100.6', '加速机3', 6);

-- ----------------------------
-- Table structure for t_load_project
-- ----------------------------
DROP TABLE IF EXISTS `t_load_project`;
CREATE TABLE `t_load_project`  (
  `id` int NOT NULL,
  `projectPath` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `userId` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_load_project
-- ----------------------------

-- ----------------------------
-- Table structure for t_one_click_load
-- ----------------------------
DROP TABLE IF EXISTS `t_one_click_load`;
CREATE TABLE `t_one_click_load`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `software` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `usrID` int NULL DEFAULT NULL,
  `module` int NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 34 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_one_click_load
-- ----------------------------

-- ----------------------------
-- Table structure for t_tools-----
-- ----------------------------
DROP TABLE IF EXISTS `t_tools-----`;
CREATE TABLE `t_tools-----`  (
  `id` int NOT NULL AUTO_INCREMENT COMMENT '主键字',
  `name` varchar(50) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '软件名',
  `host` varchar(100) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '主机名',
  `path` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '路径\r\n',
  `icoPath` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL DEFAULT '' COMMENT '图标路径',
  `module` int NOT NULL COMMENT '模块',
  `ip` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL COMMENT 'IP地址',
  `number` int NOT NULL,
  `username` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_PKID`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 231 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_tools-----
-- ----------------------------
INSERT INTO `t_tools-----` VALUES (169, 'ps', 'host2', 'd:', 'd:', 2, '', 0, '');
INSERT INTO `t_tools-----` VALUES (170, 'AE', 'host2', 'D', 'D', 2, '', 0, '');
INSERT INTO `t_tools-----` VALUES (171, 'PS', 'hots3', 'D', 'E', 3, '', 0, '');
INSERT INTO `t_tools-----` VALUES (172, 'AR', 'host4', 'E', 'E:', 4, '', 0, '');
INSERT INTO `t_tools-----` VALUES (173, 'AD', '1', '1', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\adobe_xd.png', 1, '', 0, '');
INSERT INTO `t_tools-----` VALUES (182, 'DI', 'host1', 'D', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 2, '', 0, '');
INSERT INTO `t_tools-----` VALUES (183, 'CE', 'host2', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'D', 2, '', 0, '');
INSERT INTO `t_tools-----` VALUES (185, 'DI', 'host3', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'E', 3, '', 0, '');
INSERT INTO `t_tools-----` VALUES (186, 'DI', 'host3', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'E', 3, '', 0, '');
INSERT INTO `t_tools-----` VALUES (189, 'CD', 'VD', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\icon.ico', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\icon.ico', 2, '', 0, '');
INSERT INTO `t_tools-----` VALUES (190, 'QQ', 'host1', 'D:\\tools\\QQ\\Bin\\QQ.exe', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\QQ.png', 1, '', 0, '');
INSERT INTO `t_tools-----` VALUES (191, 'EV录屏', 'host1', 'D:\\tools\\EVCapture\\EVCapture.exe', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\EV.ico', 1, '', 0, '');
INSERT INTO `t_tools-----` VALUES (194, '1', 'host2', '1', '1', 2, '', 0, '');
INSERT INTO `t_tools-----` VALUES (197, 'VS', 'host2', 'VS', 'VS', 1, '', 0, '');
INSERT INTO `t_tools-----` VALUES (198, 'A1', '节点1', '', '0', 1, '192.168.0.1', 1, '');
INSERT INTO `t_tools-----` VALUES (199, 'B1', '节点1', '', '0', 1, '192.168.0.1', 1, '');
INSERT INTO `t_tools-----` VALUES (200, 'D1', '节点2', '', '0', 1, '192.168.0.2', 1, '');
INSERT INTO `t_tools-----` VALUES (201, 'C1', '加速机1', '', '0', 1, '192.168.0.3', 1, '');
INSERT INTO `t_tools-----` VALUES (202, 'A2', '节点1', '', '0', 1, '192.168.0.4', 4, '');
INSERT INTO `t_tools-----` VALUES (203, 'B2', '节点1', '', '0', 1, '192.168.0.4', 4, '');
INSERT INTO `t_tools-----` VALUES (204, 'D2', '节点2', '', '0', 1, '192.168.0.5', 4, '');
INSERT INTO `t_tools-----` VALUES (205, 'C2', '加速机1', '', '0', 1, '192.168.0.6', 4, '');
INSERT INTO `t_tools-----` VALUES (206, 'A3', '节点3', '', '0', 1, '192.168.10.1', 2, '');
INSERT INTO `t_tools-----` VALUES (207, 'B3', '节点3', '', '0', 1, '192.168.10.1', 2, '');
INSERT INTO `t_tools-----` VALUES (208, 'D3', '节点4', '', '0', 1, '192.168.10.2', 2, '');
INSERT INTO `t_tools-----` VALUES (209, 'C3', '加速机2', '', '0', 1, '192.168.10.3', 2, '');
INSERT INTO `t_tools-----` VALUES (210, 'A4', '节点3', '', '0', 1, '192.168.10.4', 5, '');
INSERT INTO `t_tools-----` VALUES (211, 'B4', '节点3', '', '0', 1, '192.168.10.4', 5, '');
INSERT INTO `t_tools-----` VALUES (212, 'D4', '节点4', '', '0', 1, '192.168.10.5', 5, '');
INSERT INTO `t_tools-----` VALUES (213, 'C4', '加速机2', '', '0', 1, '192.168.10.6', 5, '');
INSERT INTO `t_tools-----` VALUES (214, 'A5', '节点5', '', '0', 1, '192.168.100.1', 3, '');
INSERT INTO `t_tools-----` VALUES (215, 'B5', '节点5', '', '0', 1, '192.168.100.1', 3, '');
INSERT INTO `t_tools-----` VALUES (216, 'D5', '节点6', '', '0', 1, '192.168.100.2', 3, '');
INSERT INTO `t_tools-----` VALUES (217, 'C5', '加速机3', '', '0', 1, '192.168.100.3', 3, '');
INSERT INTO `t_tools-----` VALUES (218, 'A6', '节点5', '', '0', 1, '192.168.100.4', 6, '');
INSERT INTO `t_tools-----` VALUES (219, 'B6', '节点5', '', '0', 1, '192.168.100.4', 6, '');
INSERT INTO `t_tools-----` VALUES (220, 'D6', '节点6', '', '0', 1, '192.168.100.5', 6, '');
INSERT INTO `t_tools-----` VALUES (221, 'C6', '加速机3', '', '0', 1, '192.168.100.6', 6, '');

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
  `loginStatus` int NULL DEFAULT NULL COMMENT '1：一登录 0:未登录',
  PRIMARY KEY (`PKID`, `UserName`, `Password`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 326 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_user
-- ----------------------------
INSERT INTO `t_user` VALUES (68, '1', '1', '1', '1', '1', '1', '0', '2021-03-04 19:27:50', '1', 0);
INSERT INTO `t_user` VALUES (324, '2', '2', '2', '2', '2', '2', '0', '2024-11-04 09:36:28', '1', 0);
INSERT INTO `t_user` VALUES (325, '3', '3', '3', '3', '3', '3', '1', '2024-11-04 10:52:51', '1', 0);

SET FOREIGN_KEY_CHECKS = 1;
