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

 Date: 10/09/2024 17:44:27
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
) ENGINE = InnoDB AUTO_INCREMENT = 37 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

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
) ENGINE = InnoDB AUTO_INCREMENT = 20 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_download_approval
-- ----------------------------
INSERT INTO `t_download_approval` VALUES (1, 68, '2024-08-15 13:44:17', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\debug\\qss\\default.qss', 'qss', '2024-07-29 16:54:00', '1');
INSERT INTO `t_download_approval` VALUES (2, 105, '2024-08-16 10:00:00', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\debug\\qss\\default.qss', 'qss', '2024-07-29 16:54:00', '0');
INSERT INTO `t_download_approval` VALUES (3, 68, '2024-08-16 10:02:29', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\debug\\imageformats\\qicnsd.dll', 'dll', '2020-03-28 02:38:00', '0');
INSERT INTO `t_download_approval` VALUES (4, 68, '2024-08-16 10:02:34', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\debug\\imageformats\\qsvgd.dll', 'dll', '2020-03-28 02:41:00', '0');
INSERT INTO `t_download_approval` VALUES (5, 68, '2024-08-16 10:02:38', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\debug\\imageformats\\qwbmpd.dll', 'dll', '2020-03-28 02:38:00', '0');
INSERT INTO `t_download_approval` VALUES (6, 68, '2024-08-16 10:02:51', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\debug\\imageformats\\resources\\qtwebengine_resources_200p.pak', 'pak', '2020-03-28 06:05:00', '0');
INSERT INTO `t_download_approval` VALUES (7, 105, '2024-08-16 10:25:46', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\x64\\Server.tlog\\CL.command.1.tlog', 'tlog', '2024-08-15 17:36:00', '0');
INSERT INTO `t_download_approval` VALUES (8, 105, '2024-08-16 10:25:50', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\x64\\Server.tlog\\link.write.1.tlog', 'tlog', '2024-08-15 17:36:00', '0');
INSERT INTO `t_download_approval` VALUES (9, 105, '2024-08-16 10:25:52', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\x64\\Server.tlog\\link.command.1.tlog', 'tlog', '2024-08-15 17:36:00', '1');
INSERT INTO `t_download_approval` VALUES (10, 105, '2024-08-16 11:17:06', 'D:\\1_project\\Z_project\\GitProject\\DI\\FtpServer\\Server\\debug\\resources\\qtwebengine_resources.pak', 'pak', '2020-03-28 06:05:00', '1');
INSERT INTO `t_download_approval` VALUES (11, 105, '2024-08-16 14:30:27', 'D:\\FtpData\\debug\\qss', 'dir', '2024-08-16 11:20:00', '1');
INSERT INTO `t_download_approval` VALUES (12, 105, '2024-08-19 13:33:09', 'D:\\FtpData\\debug\\position\\qtposition_winrtd.dll', 'dll', '2020-03-28 05:03:00', '1');
INSERT INTO `t_download_approval` VALUES (13, 105, '2024-08-19 13:43:18', 'D:\\FtpData\\debug\\translations\\qtwebengine_locales\\bn.pak', 'pak', '2020-03-28 06:05:00', '1');
INSERT INTO `t_download_approval` VALUES (14, 105, '2024-08-19 17:55:48', 'D:\\FtpData\\debug\\translations\\qt_da.qm', 'qm', '2024-08-06 15:11:00', '0');
INSERT INTO `t_download_approval` VALUES (15, 105, '2024-08-19 17:55:49', 'D:\\FtpData\\debug\\translations\\qt_da.qm', 'qm', '2024-08-06 15:11:00', '0');
INSERT INTO `t_download_approval` VALUES (16, 105, '2024-08-19 17:55:55', 'D:\\FtpData\\debug\\translations\\qt_en.qm', 'qm', '2024-08-06 15:11:00', '0');
INSERT INTO `t_download_approval` VALUES (17, 105, '2024-08-20 14:52:31', 'D:\\FtpData/x64', 'dir', '2024-08-19 17:36:00', '0');
INSERT INTO `t_download_approval` VALUES (18, 99, '2024-09-04 13:36:55', 'D:\\FileData\\x64\\imageformats\\122\\qwbmpd.dll', 'dll', '2024-08-30 14:15:00', '1');
INSERT INTO `t_download_approval` VALUES (19, 99, '2024-09-04 13:37:03', 'D:\\FileData\\x64\\imageformats\\122', 'dir', '2024-08-30 14:15:00', '1');

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
) ENGINE = InnoDB AUTO_INCREMENT = 59 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_fingerprint
-- ----------------------------
INSERT INTO `t_fingerprint` VALUES (56, '4d575353323100000414190408050709ced000002815910100004d8339288c14b900e46497005f00ea70c700e1003e647c00fa145764e200c900f1465714b500d33e4e005b005470fd00b2009c4501001a155f64a6002b011b6479144d00ed6444009c00d970c6003200fd64e90064158410b800bc00d3646b14c300d66478002e004070df00ac00212b6b000615d4648b001501ea64b7146b007064f2002e003f0c0001de00b31b430054146464320005018322ea1449007f3295009c01fa45b000d6004a644e00e81440645c00be008a4ca0140001c3649c00b200f670f500c5001b328600d414d164fb00a4006c419d142b01b164aa008900ff70b20040018064b2003614696458003c002264090773f91a97e60d9ffdb3ccd4f696e8260d5983a181ff1845190917f799d4936486c2fc697ea7015768a0f435816e7c5780d21dcb89242fcd625780a09f4887260a7ef95ef38f63e7069a83d38f7a43ff9fe25bb5cf9eda9ff6319d9cf73e04410533736b0098ef56786a84f5179897d3797982366cab517997c774a70d2989330a0e363079799b6681697bcee91b6d0b7a2f07d6fb9e936e1383876682824c5734480e013772f604fd5a948316d47f39795f80c4e7b86d2294798713053e9bdce93581916b5f8082e8a6fc150c4e88e791d0c37886ee31ba8cc7996e16a8a69ed1d626947f8a9447058e80f20d6ffe99f7faeb49202d01c71119540c00aa206dc0057f66d4c0ff04007e23a8800a14b62874c0835db5660314c92b70526b05c575347d680800773664a3660c14e53a83c18183d100e82b763ac0896b7b07ffc6420700ac4bfdc13b3a0d1482506d876dc3cc008240667064c314003f5f929d7488667ac142d400fe778859798478c1a81604e36d907e888bc205c24ed64fc00f00f77149c17598c3c178c108003178887bc3c2ff160096be6480d47a6a747cc2c104c01814f8818cc084c24dc1c5d5c0c159c071c105c1c6630f00fa8f9ec53ac294d78a7e1b00f9975b99c796c374717278c145c10d149999e9fefe2efd07045b9f50c06bc11bc5fdb4b6c3c19290c4c104c0c57ec3c1c07cc284cf00f2a59bc18c97c20dc5bcb81b2157fe3dc00dc55abb47c0ff7076c35ccb005bab4ec0567ec183051a04eec0a4c2c3ffc20196c5d5c2677ec088c05a0504f6cc302f0400af1e495a1301c5dca4cac701c2c11101cae33a3307c5c5e057c1ffff211000bfe5d4542bfefb2efe5cdd00f7f3b0c1c1c1c4c3079fc6d5876ac2c3c1b2d010b45ee38c77c1c3c106c5cdd6c4c1c3c2590cc576e95d7fc096c29f09c57be9527582c10400b519402a1c1189163ac3c303c4b41011c0215c1d19d5e515d7c36ec0c5c3c64a84c66594c5c405102ce046c6cdc616109b29b70731fae9fefbfcfbfcfd3a3139eb02103f5993c59742040d4201020100b4c5e446140000a2011ac8c5001d515300', 1044, 298);
INSERT INTO `t_fingerprint` VALUES (57, '4d7753533231000004343b0408050709ced000002835910100004984d9275f34ec003e608c00240033504f00d000d2649a00b234e3498300a800c36474342a01a7646d00fb019350b00090001364f9004c35f4647a005701576443345c00eb647b0090006a5038004b005d64bd00d4344b648d00d700f7646f34bf0052644e00c50146504d001501436462001d35a65b5b0043014d64c1342001a66437008601df789a004f019964f4005d35fe4265005200a964c83461000d4b7b000d00fa508600c90064648c00d8344b645700b60097422f34e1005464c3000c002e7b4e00420109648e007134e9642b003d0112232e345201e81799009e000150cc004801964ca0003a34f7649dfee1f6376c083300d6e5ef008bb88382c42192b990f6101bb4c23cb7a421113a2087a26525b0f11507db0d820a1b272d1e81ede5f958ffe2cd870d3d92d1064f809d321f68b6784976eff35340054e25e8451a51fff9e4dceac9704555780285351806faf90101939f0a33e70023124f03b983e9c5739466001212fe0fc0de390701f55e09b204e731211a590d4d2610791d368780fb09cbfe3ea3d482859f19ada06b88348928097b550eb2f8f57239367c832a0c1e868a14cbce0a1bdbcb7c832815f10650fe767f4b8c79ffc5d1ecf2b4ea750d44f502ac82f90799a2f2a2fd97c7cc8dae88ea0f78ec6ac37c203601023dd8b50c3468276959ff82c900831e7bc2698bc05bc000a705817c09006040a8c1c7f5fe6b07006840324f523101374e60c1c13b08045f51f4ff41470ac5bf41b882c0c26e0c00bc5374f6fec1c4557307c58150c3fefeff670a00a15669b46a6004009c58c64401347b596d690f00515a79a7c17ac15a4405c59c593d4e0700446160b5541034d174937e916f0478c4f54d1400d9809005c0c6cbc5c1c2c090789cfe1034db8a93c0c2ff07888cf48473ff1300ab4a89c6ba8a8458c04a04c5b38b38340400b29413f81404ee9393c0c2ffc24dc2c65bc1c1c1ff7616c5da9ea7c1c1c184c47c0666c46f3c0a0085a6fa3efff9f4c3270c0085ac38fa39c943660c005cb212fd2a13550c0060b4de3bff201b42120065be5607c175f6c1c5c2ff70c2910e045dc150c0c26ec307c2c7c9770600c3ca273afffbf509008dcb1afd38c1c4f5c00a009dcd243bff63450c0086d057c404c4c5f7755c0f0075d295c3c5a6c0c1c1c162c1cb007ee04dc296c3c172047d083488d74f9ec3c10758c43f0191d729fe7104c1c5f4c10a0046e04c054a55cb09004ce049ff9e381334ddd3a46fc0c107c4c7f7748342c02a05c58ae00ec38c050091e4f17502345cee438dc104d54a1c72220510ad1e1a05601b24de1fa438ffc10488c0f0c5c48089c4fe06737cf51c10db25a23e8792c1f2c5c197908b6b4603147a2c56fd091054f01ac6777506102e55ed382a03243559fa325003d57e5827c106102762fdfdc05676011943010201c59004ea360002005401fd3e043418455200', 1076, 299);
INSERT INTO `t_fingerprint` VALUES (58, '4d0d535332310000044e4c0408050709ced00000284f910100004a84f327ae4eea004c649c000b005c2acf00c50016601500b94e7b417c00190181647f4e2a01406406017b009f0c10010e0131145e00514f9c64fb008800434b994e67006e6474009a00642a53005201dd217100e34ee864bd00fc00fd647b4ee800d5648800c201442ae900a900144dce01e04ead36820088002c64d44e72000664f900fe01a12a7f006f00ec640d00624f9a64fa005e015d0b264e27015908be0024006e2ab300c400fa64bf00f64e4c64f600e700ee395f4ef1005764d700f001ad2aa1004401a7527600694e715e3f001201971d1c4f2301b11c4400f301cf459a005200f6647c00294efa30246721e694161d2c570c4a71349e281fc6e251667e80ea6844051148fffa05fd12029f9b86c723f236738181cf87ff46b0f9f3048b5d97768bce32eed17921024f844d3b176e2af75214429e47c9099f8083c9b23c52e1a008d3008be294e3819db0e8f6f66cd29c437946dc50819212127f94fe4ec5777f06988f80c29962b31b0dc2f63d8d08068ece7600e305b3f56ff567b38ef212093a92827f84cd84225937f5a64ce77ace097b5d0eb6f8948122dd7efc2e0c22854307e64b2611ff12250db76bf3439c061a6cb67d53f96ec70fff8181360e4e07e2be73794a76c9896b89ea40e204db8fcb8f729cd6f77e203a010257dbe0074ee01134ff08005b22748e81350a00b322b5c0c43bfe710d00c325a8517c29551000e335803a837a8ec0c0c3fec1c1cf00e1737c5ac3ffc27cc200e97068fbff840b0053546fca65c05b08009e91fac50f310a00f65b8c417b834901715e64c2c03a700c4e746360c1586fc200a72af6c0ff400b00596a69ca6a5b1300fc6e49c1803478555bc20500776f748c501300f7738644c1838ec385c0c15a08c57b702ec0c065c1030010740d8f1200f3838c75077ec58c6a5b701600fa4b9080d8c1c2c266555d05c0134f069d978388c107786926c04a150103a45383c6c28a6ac2ffc2fdad1304ada989c1c1c48007675c16c10300eba80c3b15054ca890c1c175c341c087b0c3c0510300ea6813c44601d0c30ffeff05ff224501aec862c28406c0c5d10500cfc913fe3a0a04eecbe7c1fbfd28fb0e0546cb9e85c4c1c2017c7a420199ce5a84c13b73f9b10e009cd257c00666c68cc0c642c10e01cdd6a68cc1c2c1c1c4c40588c44a01cfe18cc4c7cc00d4a8232bc1c15c19d40437e7c13784c5c3c65b918f8c6b0400f8e622ff0d0487e67dc8c49575b60604bbeb30c0c04f08c5cae86cfc4ec2c00d006dee57eec384c1c06f0dc5adea01c3978bc1690ac5c2eb74c0c1c0c3ff93ce00bfbc4da091ff4f05c55cf714680900c9f334afc27a490178f44c423ecd0079bb48ff5530050078fd3ecc0810881243c25a51005e792f49fdfe04d57d2b74af19110a2fad3ac1c4b0c282c2c4c5c4a9c2958ec07e0810655922c3f58ffec0ff03108b9813fb4d11736109ff5287001d0d00020100c6003935044c017e014a4000c519411c', 1102, 300);

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
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 570 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_ip
-- ----------------------------
INSERT INTO `t_ip` VALUES (413, '192.168.0.1', '节点1', 'A1', 1, 0, '', '0', 1);
INSERT INTO `t_ip` VALUES (414, '192.168.0.1', '节点1', 'B1', 1, 0, '', '0', 1);
INSERT INTO `t_ip` VALUES (415, '192.168.0.2', '节点2', 'D1', 1, 0, '', '0', 1);
INSERT INTO `t_ip` VALUES (416, '192.168.0.3', '硬件加速机1', 'C1', 1, 0, '', '0', 1);
INSERT INTO `t_ip` VALUES (417, '192.168.0.4', '节点1', 'A2', 1, 0, '2', '0', 4);
INSERT INTO `t_ip` VALUES (418, '192.168.0.4', '节点1', 'B2', 1, 0, '2', '0', 4);
INSERT INTO `t_ip` VALUES (419, '192.168.0.5', '节点2', 'D2', 1, 0, '2', '0', 4);
INSERT INTO `t_ip` VALUES (420, '192.168.0.6', '硬件加速机1', 'C2', 1, 0, '2', '0', 4);
INSERT INTO `t_ip` VALUES (421, '192.168.10.1', '节点3', 'A3', 1, 0, '', '0', 2);
INSERT INTO `t_ip` VALUES (422, '192.168.10.1', '节点3', 'B3', 1, 0, '', '0', 2);
INSERT INTO `t_ip` VALUES (423, '192.168.10.2', '节点4', 'D3', 1, 0, '', '0', 2);
INSERT INTO `t_ip` VALUES (424, '192.168.10.3', '硬件加速机2', 'C3', 1, 0, '', '0', 2);
INSERT INTO `t_ip` VALUES (425, '192.168.10.4', '节点3', 'A4', 1, 0, '', '0', 5);
INSERT INTO `t_ip` VALUES (426, '192.168.10.4', '节点3', 'B4', 1, 0, '', '0', 5);
INSERT INTO `t_ip` VALUES (427, '192.168.10.5', '节点4', 'D4', 1, 0, '', '0', 5);
INSERT INTO `t_ip` VALUES (428, '192.168.10.6', '硬件加速机2', 'C4', 1, 0, '', '0', 5);
INSERT INTO `t_ip` VALUES (429, '192.168.100.1', '节点5', 'A5', 1, 0, '5', '0', 3);
INSERT INTO `t_ip` VALUES (430, '192.168.100.1', '节点5', 'B5', 1, 0, '5', '0', 3);
INSERT INTO `t_ip` VALUES (431, '192.168.100.2', '节点6', 'D5', 1, 0, '5', '0', 3);
INSERT INTO `t_ip` VALUES (432, '192.168.100.3', '硬件加速机3', 'C5', 1, 0, '5', '0', 3);
INSERT INTO `t_ip` VALUES (433, '192.168.100.4', '节点5', 'A6', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (434, '192.168.100.4', '节点5', 'B6', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (435, '192.168.100.5', '节点6', 'D6', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (436, '192.168.100.6', '硬件加速机3', 'C6', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (437, '192.168.250.100', 'host', 'WPS', 3, 0, '', '0', 4);
INSERT INTO `t_ip` VALUES (438, '192.168.250.200', 'host', 'Git', 2, 0, '22', '0', 2);
INSERT INTO `t_ip` VALUES (612, '192.168.10.2', '节点4', 'VSCode', 1, 0, '299', 'c:////', 2);
INSERT INTO `t_ip` VALUES (613, '192.168.10.1', '节点3', 'QQ', 2, 0, '299', 'D:////', 2);

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
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

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
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_load_project
-- ----------------------------

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
) ENGINE = InnoDB AUTO_INCREMENT = 201 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = Dynamic;

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
INSERT INTO `t_tools` VALUES (197, 'VS', 'host2', 'VS', 'VS', 1);

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
) ENGINE = InnoDB AUTO_INCREMENT = 301 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_user
-- ----------------------------
INSERT INTO `t_user` VALUES (68, '1', '1', '1', '1', '1', '1', '0', '2021-03-04 19:27:50', '1', 0);
INSERT INTO `t_user` VALUES (80, '2', '2', '2', '', '', '', '0', '2024-06-21 09:52:01', '2', 2);
INSERT INTO `t_user` VALUES (81, '2', '2', '2', '', '', '', '0', '2024-06-21 09:54:54', '2', 2);
INSERT INTO `t_user` VALUES (82, '3', '3', '3', '3', '3', '3', '0', '2024-06-21 13:39:07', '1', 1);
INSERT INTO `t_user` VALUES (83, '44', '3', '梁超群', '33', '3', '3', '0', '2024-06-24 10:14:08', '1', 2);
INSERT INTO `t_user` VALUES (84, '21', '21', '21', '21', '21', '21', '0', '2024-06-24 10:41:30', '2', 2);
INSERT INTO `t_user` VALUES (85, '22', '22', '22', '22', '22', '22', '0', '2024-06-24 10:41:39', '1', 2);
INSERT INTO `t_user` VALUES (86, '23', '23', '23', '23', '23', '23', '0', '2024-06-24 10:41:49', '2', 2);
INSERT INTO `t_user` VALUES (87, '31', '31', '31', '31', '', '31', '0', '2024-06-24 11:52:43', '1', 2);
INSERT INTO `t_user` VALUES (88, '32', '32', '32', '32', '32', '32', '0', '2024-06-24 11:52:54', '1', 2);
INSERT INTO `t_user` VALUES (89, '33', '33', '33', '33', '3', '', '0', '2024-06-24 11:53:03', '1', 2);
INSERT INTO `t_user` VALUES (90, '34', '34', '34', '', '', '', '1', '2024-06-24 11:53:18', '1', 2);
INSERT INTO `t_user` VALUES (91, '35', '35', '35', '', '', '', '1', '2024-06-24 11:53:28', '0', 2);
INSERT INTO `t_user` VALUES (92, '41', '41', '41', '41', '41', '41', '1', '2024-06-24 17:31:47', '1', 2);
INSERT INTO `t_user` VALUES (93, '42', '444', '42', '42', '42', '42', '1', '2024-06-24 17:31:59', '0', 2);
INSERT INTO `t_user` VALUES (94, '43', '434', '43', '434', '43', '43', '1', '2024-06-24 17:32:13', '2', 0);
INSERT INTO `t_user` VALUES (95, '45', '444', '44', '44', '44', '44', '1', '2024-06-24 17:32:30', '1', 0);
INSERT INTO `t_user` VALUES (96, '46', '46', '46', '46', '46', '46', '1', '2024-06-24 17:32:48', '0', 0);
INSERT INTO `t_user` VALUES (97, '47', '47', '47', '47', '47', '47', '1', '2024-06-24 17:33:01', '0', 0);
INSERT INTO `t_user` VALUES (98, '48', '48', '48', '48', '48', '48', '0', '2024-06-24 17:33:09', '0', 0);
INSERT INTO `t_user` VALUES (99, '49', '49', '49', '49', '49', '49', '1', '2024-06-24 17:33:21', '1', 0);
INSERT INTO `t_user` VALUES (283, 'wz', '1', '1', '1', '1', '1', '1', '2024-09-04 13:34:06', '1', 0);
INSERT INTO `t_user` VALUES (298, '14', '14', '14', '14', '14', '14', '0', '2024-09-09 08:54:17', '1', 0);
INSERT INTO `t_user` VALUES (299, '4', '4', '4', '4', '4', '4', '0', '2024-09-09 10:08:27', '1', 0);
INSERT INTO `t_user` VALUES (300, '15', '15', '15', '15', '15', '15', '0', '2024-09-09 12:28:21', '0', 0);

SET FOREIGN_KEY_CHECKS = 1;
