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

 Date: 24/09/2024 10:27:59
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
) ENGINE = InnoDB AUTO_INCREMENT = 37 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

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
INSERT INTO `t_download_approval` VALUES (20, 283, '2024-09-23 09:45:30', 'D:\\FileData\\vip\\wzz\\1111\\wps.png', 'png', '2024-09-23 09:23:00', '0');
INSERT INTO `t_download_approval` VALUES (21, 283, '2024-09-23 09:45:33', 'D:\\FileData\\vip\\wzz\\1111\\wps.png', 'png', '2024-09-23 09:23:00', '1');
INSERT INTO `t_download_approval` VALUES (22, 283, '2024-09-23 09:51:09', 'D:\\FileData\\debug\\44\\imageformats\\qwebpd.dll', 'dll', '2024-08-21 17:15:00', '1');
INSERT INTO `t_download_approval` VALUES (23, 283, '2024-09-23 10:08:09', 'D:\\FileData\\x64\\imageformats\\12345\\qsvgd.dll', 'dll', '2024-09-06 13:59:00', '1');

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
) ENGINE = InnoDB AUTO_INCREMENT = 76 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_fingerprint
-- ----------------------------
INSERT INTO `t_fingerprint` VALUES (57, '4d7753533231000004343b0408050709ced000002835910100004984d9275f34ec003e608c00240033504f00d000d2649a00b234e3498300a800c36474342a01a7646d00fb019350b00090001364f9004c35f4647a005701576443345c00eb647b0090006a5038004b005d64bd00d4344b648d00d700f7646f34bf0052644e00c50146504d001501436462001d35a65b5b0043014d64c1342001a66437008601df789a004f019964f4005d35fe4265005200a964c83461000d4b7b000d00fa508600c90064648c00d8344b645700b60097422f34e1005464c3000c002e7b4e00420109648e007134e9642b003d0112232e345201e81799009e000150cc004801964ca0003a34f7649dfee1f6376c083300d6e5ef008bb88382c42192b990f6101bb4c23cb7a421113a2087a26525b0f11507db0d820a1b272d1e81ede5f958ffe2cd870d3d92d1064f809d321f68b6784976eff35340054e25e8451a51fff9e4dceac9704555780285351806faf90101939f0a33e70023124f03b983e9c5739466001212fe0fc0de390701f55e09b204e731211a590d4d2610791d368780fb09cbfe3ea3d482859f19ada06b88348928097b550eb2f8f57239367c832a0c1e868a14cbce0a1bdbcb7c832815f10650fe767f4b8c79ffc5d1ecf2b4ea750d44f502ac82f90799a2f2a2fd97c7cc8dae88ea0f78ec6ac37c203601023dd8b50c3468276959ff82c900831e7bc2698bc05bc000a705817c09006040a8c1c7f5fe6b07006840324f523101374e60c1c13b08045f51f4ff41470ac5bf41b882c0c26e0c00bc5374f6fec1c4557307c58150c3fefeff670a00a15669b46a6004009c58c64401347b596d690f00515a79a7c17ac15a4405c59c593d4e0700446160b5541034d174937e916f0478c4f54d1400d9809005c0c6cbc5c1c2c090789cfe1034db8a93c0c2ff07888cf48473ff1300ab4a89c6ba8a8458c04a04c5b38b38340400b29413f81404ee9393c0c2ffc24dc2c65bc1c1c1ff7616c5da9ea7c1c1c184c47c0666c46f3c0a0085a6fa3efff9f4c3270c0085ac38fa39c943660c005cb212fd2a13550c0060b4de3bff201b42120065be5607c175f6c1c5c2ff70c2910e045dc150c0c26ec307c2c7c9770600c3ca273afffbf509008dcb1afd38c1c4f5c00a009dcd243bff63450c0086d057c404c4c5f7755c0f0075d295c3c5a6c0c1c1c162c1cb007ee04dc296c3c172047d083488d74f9ec3c10758c43f0191d729fe7104c1c5f4c10a0046e04c054a55cb09004ce049ff9e381334ddd3a46fc0c107c4c7f7748342c02a05c58ae00ec38c050091e4f17502345cee438dc104d54a1c72220510ad1e1a05601b24de1fa438ffc10488c0f0c5c48089c4fe06737cf51c10db25a23e8792c1f2c5c197908b6b4603147a2c56fd091054f01ac6777506102e55ed382a03243559fa325003d57e5827c106102762fdfdc05676011943010201c59004ea360002005401fd3e043418455200', 1076, 299);
INSERT INTO `t_fingerprint` VALUES (73, '4db353533231000004f0f50408050709ced0000028f1910100005d841d2e7af0d0004864880031004b946e00fd00c4644b0000f15a647e000d011764aef0a4001f565900c8012b947e001901d064ea00b4f04f64840032014764baf087001d64c000ed014190bc006a008d64c80015f14f33740042003e6444f02d0066649a00130039945f00e4004064b300faf0c6645200b3002450bdf0e100396440007c00d09465009000ec64ab0025f1b164a80020018f6426f0aa00d1649100f9016e941f0097004e6457004af1d664f00089006e02eaf07300ac0472002a00d4948200b20015646800c2f035644700e600846476f00e01c464bd0079002acd9400140158640900bef0a033c4000801fe646ef06e00ef6413000900cb947f0061006e64a90054f1f96418003a01f75594f02c000064410fc7348e8864f49d89bd8205fe8104f401d90c55045489e8f729135d0c86f05bec3ef5546e396f7183a90349fc2021c17c457d1f001de8b8b699d721937b016385c8fe020ccfecf473ff110ae76a1ff783de0fbe7c6ffdcf0c2f6e827b1b9b280acdf752049072b9f26b7c400671f820f411fd279576f6f50713fc0afda0f541893e049bfdeefeb6d899edc1e168e3c906440696e1c184ac85c60cb0e85595f621a87d5ef0567c696d5a54efe295f25a916f2311029a214361f80ce508b98277cc660a97db3509b1fab8ff39f26f174a73b4f71cf4810c4c8cbdfdf6101cfc45e2a08a5974526cb3868a08abf1fe0679821f055f0487019282a3fcbc82c2846a868a22667ab393021736075b3fe6050a96af87abff1fa17f3fe53b05f2a52331030060df70c7fb01781970c084a1690bf0941a74c06ac2a8c1c4314b08009e2277afc1c4320200b52980c1c1003ada665b06004030a759c4f5018b30777704c59334f03f1400ca408605ff8c8779726ac10800b244f30ffefcc2390800824b6031666709004f4ea27e6e300200f76040c1dd007a937090c17ec1c0045a6b9cc1821600d85d5678c47088c266c0944ecb00b897918382c1846dc200bf9c88c082c00500066e170e501b00b984900491c56d72c170c2ffc2047ac5710500c1851a38c100c47a1f460c00668f2c2e2eb1c306001d9a4c97c124f0eb9aa47577884589760f7a83c080c111c5e49954817e9dc28868c200aa5621c0c0fd4214c524ae20fe4f44fd30fe91401df0e47da2c36777477c7a3067ff7b0c005475e045d7fcff381c0088740cf80dfcff46c0ffc13bfdfa0c2dfefbc0feff3bffc43009002bb34f599d0b04c1b24f64c0c1c1075f2ef0c8b9a2c183c4068cc5335bc4fec3fec3b9c1c0329ec1c2a062c0bd0d0449bda4c1c2c3c301c1969a1200aac0a4c306c69f31c386fec4c1aac000c53228350700bdc4f5475df3017ed249c20ec599d3ca2efcc0fbfcf738fe2ae50160dfccfefe39faf80cfcfffe3effff3ac0f90cfa2000dabfa905c1c731c1c3c293c47c3ac180307f808dc20d104d6ce970c2c27cfe8303c5bde6c7c1050060e740077e0df04be9436a91c0c10080234126040085f692920ef06efac3c1fcfd3ff4ffdb3510900856fe33f5fb31fcfefefdfcfa3cfcfb0dfec0fec0fffd3bfdfe0bfffdfefffec005fefa0fc1fdfdfefdfc38fff930feffc0ffc208d5c108b0c3ff33fc0410030c3eab0410591130c2680414e01243690410a8e5493cf711bf2a43fffe3bfef9f511163c3a9205d51c38c48203108f3f603e5246f01843010201004f00dcb3010100780108020004e94452', 1264, 319);
INSERT INTO `t_fingerprint` VALUES (74, '4c4b53533231000005080b0408050709ced00000290991010000648435379f08d0007864b8001900a56cc500ec004164680008094f6499001501a4645208f0004f648000d901d16ceb00f5003b4c8100d90855647c00270137643908b7005a3c8b00fd01756c0701e400b51009006f089364c70040010161f8087e00a2514a00ac00ef6c1700fc00544e3d004a08ab4ca200e500f0649508f6005664d0007d002b4a7500000145649a00af08e824ea00ce006b4b7b0885006f64df005c009e4572002501c364a6001a093664a00039019f644f089400e86406017200b13203019300ac4e8b002b093d646c004301cc64af08590158609b00fe000c6caf00340084645700ed085f648400ab00c45cab089a0082648100c201dd6c88001901d6641c000309426474001901036499087a007e648100bd00fa6cbf002e014964c601cf08b33e3400ca001f5b0709a400af3eb20098008c6c61006700f364b0004a098f645e004b017b643c4e541e1ad80561946e7720e4a16600ca0d60eecbf16305958c1116508fd0f7470c4778a00239e73d1ba4fa3288068e147e540fe7fe18325c23fc2c708afb751a7115197082c7948807367c6a09440b26f16215697d226e836e10f11bf6420a95fa1f07a6e61602077f2707d60846111203c5d8fdbef896f4f088820d227281e395ab9b506c7d8231f3ff000f999be9cdfe72812bf9d97b07f04e723a6d27f1f3e5c5d280ffa5f09c743879b0ffa9ed1a109f04bf08eb915a038505d0058f0114fd8d0d4e11e80777885f359d7ce14c8748db080f96caeb69856782be876c7d3afe2bf7ac081820f0ea02193a966f8baf0d1f5772833d941c05e80d1d06a17409e5d80ae70cbbf7fc07c4f720d48c8b7b102efdcc93408313056485aaf0e6fd50014c0e08ff7582c98a0e8d940d08fd62150dfb970da78a080aa2f5ae875c847cdad320adb4c932ab847b57c26d9afc5d20f901074721c10b00ad34466c6e8d06009f2406fff2ff0c089f39032e58ffce0093338180c1c070c2ce004a35f5c146fffd3ecf009b360dc0fffd5bc0380405d143132f0400d7821a5c0101b05a90c386b00705b85e8c887c12008e66e7f63a2ffdc0fdc181421508626af4c03b40fd35c400015b6c6b8454c300406666c4fe5908004075ff233005007d7974400605ab7d0930c00f005e7e85ca80c2ff7e6bc0c8007b8c7178c1c1664ad2010598aa7fc17884904669380f01aa9783c1c101c0c70201b29b132bfefbc01608ab9c8382c0c2be71c563720600e29d243b4c080860a7e7c02ac0393035180189acfafdfee22ff9c864c00c005baf9958c57f5907003db6573ac140110112b8e4c1623a3b493934c0feff4609c5d0bf2f343fc11900100cde657bfe31c2fcff3305fefaf736170036c9dc924139f7ff31c02a7317c5ebcfb9c0c1c375c28846c1c5c9fe6ac10c009b177dc6ccc0c283fea303c5ecd73cc1160048d8dc82fffb26fe213d37420dc540db5fc1c25879fec33f0e05bfdfa9c3c4a1c107c26fc90d0045e057c1ae74c48b0900a4e329faeefffb0c019ae8628b06c590ef6cc5c25717005a29d3362cfcfdfdfdfd5787ff350101c2ee3d40453a040594f040210b005431568e79c0a00b0059f495c0c46189c4040096f78cfdfa0b018ffa53ff08c577fedefffafaf71d03c518fa5bc11d10d902c043c187cac5c19174705cbd8c0118730349a00e10a833b2c8fcfdc0fefefc38fcfcf4fc0510d60a43054a0118da0a40650a106f104ac82efdfffff504d5af15414204109a1957e305156a2437c2cbc400', 1288, 320);
INSERT INTO `t_fingerprint` VALUES (75, '4adf535332310000039ca00408050709ced000002f9d910100004b834120b89cff00f364e700db0147f8b6004501d6643a001e9d3d5fe5004a019064ef9c4b01d2647100ce01daf86e00380155643c00ba9c1763e0009b00b964869c8100ed64d000dd0150feb2003701d0646800479dcf64c30051019a648c9c43014464cf009d016af8ab005c01ec644500529d4e64a500a000af64b39c8700f764fb00b1007aaca700290146644900f89c5464ff000801f164ab9c4f01e864f20083015bf8c0005901d764dd01209db2120701c700523af79ca4008e613100fe01cd94b3a013a0e3ac0cf23e961f10300b610808780695c4fa4d8b2c86e4fc9673317e987e1e685784e91bbe9756083a112b7f8e1d20890e9e19f2ef6adc989bfbb687a373fc12d1fc8f870104e5fc948dbb6705eb85006c8afcf8c2149cf5515f4278680c96080017510491169c221291dbfc326ae9777f7f146fd88f120f9b7da6fc4c704a675d79717ba37095e02e645b118df96bf06d1d6d1fd5fc8514558a9e9897f2747aa9709c025ae7738153708981530a8c83287985161efa767b986bbe835f1fb772e530029dfb189404009caf67629b01d1607467c13b0d036e697afec2c08b056efc9401f96c69fac007c0c15f0600ff808cc14cc1069c93896dc16807c5ab8aed70c0c00700b34cf7c361c0330f0106924c717b5cc3c162c111001a988317c262c069c1ffb410029a98896ac27bc2acc0708e01df9e7dc2c04e7472fc640d00a5a16bb67ec35ffc8f1400dea5b8c27d5e677144c1fe53d000e1377cc27ec2647e9ec046600500e4ab09c03b0d036fb9898ec1c1c1a88b0d9d05c99379c3c1466ac2840013e0a493974c74c3f64b47170112e9678cc13c7d8458684b0bc5bffe71fdfdfbfdfdfd05c0fc99118a0056c155d7011764a682c0c3c3c345c1c25d590410ff0a2df30513490c70a309106fd557c3fcc0fffd0710ddd637fe61310710d816403bfdfcbb0510cd185ac33b10136218b7c1c4c4c306c58a5dc1c2880410d2de50448a10141db4c18850c2c7e0c0c07b701611d30bae5dc0c3c1c1c4c357c1c35fff7eff4c0510232140632b0410fe214004fe0f8caa25cffefe1d3efdfeac0510a52b4988c610a9b142c115111430755fc15cc5c4c2c3c4c007c0c062c2c17105106afd57639a11703953c0ff3ac00f8cae44c63cfdfa3efbf8b605108f47468fc610f2d54dff0410e24d9244078ce94d4f2b0310b350555d0510cc586423974203854201020100d8c420489c0000ae0150d7c5001ad95300', 924, 321);
INSERT INTO `t_fingerprint` VALUES (76, '4c615353323100000522230408050709ced000002923910100004785cf337022e0006564b4002a000b12c000d8000a648c00e1226564ad002801ee64c5222d012b649b008c015146dc00b900802cbf004823f3645d008500b5649a225b0157648700a7017946d0005401396421008022075286006100b56432225e01566458008e006a6c7600ff00f264510016230964b2001401df645e2215015c644600c901e741a90094007564eb00e222e6562b00cd002e64322229015c64f0006a000a7450008a00f0642f0037232f612a009500ac6407232701a44f0b01e4012a678c004d00f759a8003e22ee33aa00cd003f646022cb00ed649a00e6011e465a00ba006a30100014231e5d3300d400a06465223e014664af008e014146bb004f014264b5007e22f3641900e800a440c02252013f642e0080014a4160006800ef642c0050233a640301820042409e2229007535c57b9f749f2148072a15b6f5cc12c8dd578f997fb5037f7a5823e0112111dd01c413372f64fc3111361428716759c67db97a26ac4fa085a1fc81d583e104c81698fcac8ef926e22809ffd4d848027a80b2fb0689d85b6f818a82dd0bd611eadcf883468027018b8cf3bbabeda9ec7af053dcb4d390f3d103b57ecf6d9720ac8af68862828e7eb2259e876585198990ffb1a9d007ee8c720c3f7c1720dc91260b438845837b236702418f96f587010b580ef95b82c8778c7b6aa7bd8fbe01df121c89272b5b86f983aaf97f839cd0bfed7b7e3d85788bf3a8181471f15103847d6e2a4204bef5de054ff2bd5d64813503525433efd6ce4d07c1f19dee09034925480afd853506ab85185ffb7806fcd0ff810bd4dc64fbfef42f0970fedca14780c9060a0d0ffd73a24a78530b5a82ba895e25d6f24fcf7effc2204923039920a707005e2472e3c0c1470300edef7afa2c01c92c7dc2ff075bc5e1fec0381200f0f380c5e27fc168773ec1c1009e0971590900fd434cc26e5c0f01054a805905c1fae353c2c10a010690836fe35bc00c01065cb86559e3660400865f7706fd1023047793c470c10565c4e3c045c1640a0043656e666a3e0c010569436fc470fe7c06005b6ca852fa370005808f93c0a169fae3c0ff6a6a12001b8578455bc1c0c06bc0b30405c488063d06004b496d76e20a00a69377c1aec1fa4b0900ae94fa473b540322a799745cc113c408a4ae6e747effc27304660e22e8ad86c2ffc2b3c15e2c0008ab908374bb670622f0b313c1140018b6865bff7ec081c15b05c1c4260159b96d6a04c5e5bc2e421500ddbc7d05c0c670c1c07773c06705090579bf67c0c0c258040405c4c406310400d502838d2701ddca0cc02fcc0065ec66c143c2c0c1c100a6f276780a00abd1383d3066020027d369c0cd00c1f402fe382f110079d878e2c3756b66ffc04e0905e6da0940ff410cc573e54b756d59c10500b0e467dd71070048e56097540d22b7f106fe4038c8007ddeea35ffff29c038c00a327b01f4c0ffff39c03b1037081072046207ff7ee01010cf0d96c20790c58068780610d710d2fec50c0610b312102a800715f71522c140fe05d5901356c392081059179bc0c7e271041098180639ff0c32b2181ac0fd38e90715b6207ac4c2a703d40f260bff04109c272038ff0132b129222a0610072b221afe0610362d5c057e0332be302dc02b04d5eb320b431a103140d705ff3265fffe462bfeff05363326115d4250a106d563476bc3c7c8c304105f43a59f02102a4853c1c610356a51c004109d4b8c200632ac4e46c00310774e45dd0210b85143c0c610b87341ff0310d254f2c00e326e58cfc1fcfc3cfafedf2d00', 1314, 322);

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
) ENGINE = InnoDB AUTO_INCREMENT = 1107 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_ip
-- ----------------------------
INSERT INTO `t_ip` VALUES (413, '192.168.0.1', '节点1', 'A', 1, 0, '300', '0', 1);
INSERT INTO `t_ip` VALUES (414, '192.168.0.1', '节点1', 'B', 1, 0, '300', '0', 1);
INSERT INTO `t_ip` VALUES (415, '192.168.0.2', '节点2', 'D', 1, 0, '300', '0', 1);
INSERT INTO `t_ip` VALUES (416, '192.168.0.3', '硬件加速机1', 'C', 1, 0, '300', '0', 1);
INSERT INTO `t_ip` VALUES (417, '192.168.0.4', '节点1', 'A', 1, 0, '4', '0', 4);
INSERT INTO `t_ip` VALUES (418, '192.168.0.4', '节点1', 'B', 1, 0, '4', '0', 4);
INSERT INTO `t_ip` VALUES (419, '192.168.0.5', '节点2', 'D', 1, 0, '4', '0', 4);
INSERT INTO `t_ip` VALUES (420, '192.168.0.6', '硬件加速机1', 'C', 1, 0, '4', '0', 4);
INSERT INTO `t_ip` VALUES (421, '192.168.10.1', '节点3', 'A', 1, 0, '299', '0', 2);
INSERT INTO `t_ip` VALUES (422, '192.168.10.1', '节点3', 'B', 1, 0, '299', '0', 2);
INSERT INTO `t_ip` VALUES (423, '192.168.10.2', '节点4', 'D', 1, 0, '299', '0', 2);
INSERT INTO `t_ip` VALUES (424, '192.168.10.3', '硬件加速机2', 'C', 1, 0, '299', '0', 2);
INSERT INTO `t_ip` VALUES (425, '192.168.10.4', '节点3', 'A', 1, 0, '5', '0', 5);
INSERT INTO `t_ip` VALUES (426, '192.168.10.4', '节点3', 'B', 1, 0, '5', '0', 5);
INSERT INTO `t_ip` VALUES (427, '192.168.10.5', '节点4', 'D', 1, 0, '5', '0', 5);
INSERT INTO `t_ip` VALUES (428, '192.168.10.6', '硬件加速机2', 'C', 1, 0, '5', '0', 5);
INSERT INTO `t_ip` VALUES (429, '192.168.100.1', '节点5', 'A', 1, 0, '298', '0', 3);
INSERT INTO `t_ip` VALUES (430, '192.168.100.1', '节点5', 'B', 1, 0, '298', '0', 3);
INSERT INTO `t_ip` VALUES (431, '192.168.100.2', '节点6', 'D', 1, 0, '298', '0', 3);
INSERT INTO `t_ip` VALUES (432, '192.168.100.3', '硬件加速机3', 'C', 1, 0, '298', '0', 3);
INSERT INTO `t_ip` VALUES (433, '192.168.100.4', '节点5', 'A', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (434, '192.168.100.4', '节点5', 'B', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (435, '192.168.100.5', '节点6', 'D', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (436, '192.168.100.6', '硬件加速机3', 'C', 1, 0, '6', '0', 6);
INSERT INTO `t_ip` VALUES (974, '192.168.0.1', '节点1', '夸克', 4, 0, '299', 'D：////', 1);
INSERT INTO `t_ip` VALUES (975, '192.168.0.2', '节点2', '夸克', 4, 0, '299', 'D：////', 1);
INSERT INTO `t_ip` VALUES (976, '192.168.0.3', '加速机1', '夸克', 4, 0, '299', 'D：////', 1);
INSERT INTO `t_ip` VALUES (977, '192.168.0.4', '节点1', '夸克', 4, 0, '299', 'D：////', 4);
INSERT INTO `t_ip` VALUES (978, '192.168.0.5', '节点2', '夸克', 4, 0, '299', 'D：////', 4);
INSERT INTO `t_ip` VALUES (979, '192.168.0.6', '加速机1', '夸克', 4, 0, '299', 'D：////', 4);
INSERT INTO `t_ip` VALUES (980, '192.168.10.1', '节点3', '夸克', 4, 0, '299', 'D：////', 2);
INSERT INTO `t_ip` VALUES (981, '192.168.10.2', '节点4', '夸克', 4, 0, '299', 'D：////', 2);
INSERT INTO `t_ip` VALUES (982, '192.168.10.3', '加速机2', '夸克', 4, 0, '299', 'D：////', 2);
INSERT INTO `t_ip` VALUES (983, '192.168.10.4', '节点3', '夸克', 4, 0, '299', 'D：////', 5);
INSERT INTO `t_ip` VALUES (984, '192.168.10.5', '节点4', '夸克', 4, 0, '299', 'D：////', 5);
INSERT INTO `t_ip` VALUES (985, '192.168.10.6', '加速机2', '夸克', 4, 0, '299', 'D：////', 5);
INSERT INTO `t_ip` VALUES (986, '192.168.100.1', '节点5', '夸克', 4, 0, '299', 'D：////', 3);
INSERT INTO `t_ip` VALUES (987, '192.168.100.2', '节点6', '夸克', 4, 0, '299', 'D：////', 3);
INSERT INTO `t_ip` VALUES (988, '192.168.100.3', '加速机3', '夸克', 4, 0, '299', 'D：////', 3);
INSERT INTO `t_ip` VALUES (989, '192.168.100.4', '节点5', '夸克', 4, 0, '299', 'D：////', 6);
INSERT INTO `t_ip` VALUES (990, '192.168.100.5', '节点6', '夸克', 4, 0, '299', 'D：////', 6);
INSERT INTO `t_ip` VALUES (991, '192.168.100.6', '加速机3', '夸克', 4, 0, '299', 'D：////', 6);
INSERT INTO `t_ip` VALUES (992, '192.168.0.1', '节点1', '迅雷', 2, 0, '299', 'D://', 1);
INSERT INTO `t_ip` VALUES (993, '192.168.0.2', '节点2', '迅雷', 2, 0, '299', 'D://', 1);
INSERT INTO `t_ip` VALUES (994, '192.168.0.3', '加速机1', '迅雷', 2, 0, '299', 'D://', 1);
INSERT INTO `t_ip` VALUES (995, '192.168.0.4', '节点1', '迅雷', 2, 0, '299', 'D://', 4);
INSERT INTO `t_ip` VALUES (996, '192.168.0.5', '节点2', '迅雷', 2, 0, '299', 'D://', 4);
INSERT INTO `t_ip` VALUES (997, '192.168.0.6', '加速机1', '迅雷', 2, 0, '299', 'D://', 4);
INSERT INTO `t_ip` VALUES (998, '192.168.10.1', '节点3', '迅雷', 2, 0, '299', 'D://', 2);
INSERT INTO `t_ip` VALUES (999, '192.168.10.2', '节点4', '迅雷', 2, 0, '299', 'D://', 2);
INSERT INTO `t_ip` VALUES (1000, '192.168.10.3', '加速机2', '迅雷', 2, 0, '299', 'D://', 2);
INSERT INTO `t_ip` VALUES (1001, '192.168.10.4', '节点3', '迅雷', 2, 0, '299', 'D://', 5);
INSERT INTO `t_ip` VALUES (1002, '192.168.10.5', '节点4', '迅雷', 2, 0, '299', 'D://', 5);
INSERT INTO `t_ip` VALUES (1003, '192.168.10.6', '加速机2', '迅雷', 2, 0, '299', 'D://', 5);
INSERT INTO `t_ip` VALUES (1004, '192.168.100.1', '节点5', '迅雷', 2, 0, '299', 'D://', 3);
INSERT INTO `t_ip` VALUES (1005, '192.168.100.2', '节点6', '迅雷', 2, 0, '299', 'D://', 3);
INSERT INTO `t_ip` VALUES (1006, '192.168.100.3', '加速机3', '迅雷', 2, 0, '299', 'D://', 3);
INSERT INTO `t_ip` VALUES (1007, '192.168.100.4', '节点5', '迅雷', 2, 0, '299', 'D://', 6);
INSERT INTO `t_ip` VALUES (1008, '192.168.100.5', '节点6', '迅雷', 2, 0, '299', 'D://', 6);
INSERT INTO `t_ip` VALUES (1009, '192.168.100.6', '加速机3', '迅雷', 2, 0, '299', 'D://', 6);
INSERT INTO `t_ip` VALUES (1053, '192.168.0.1', '节点1', '百度网盘', 3, 0, '299', 'F：/', 1);
INSERT INTO `t_ip` VALUES (1054, '192.168.0.2', '节点2', '百度网盘', 3, 0, '299', 'F：/', 1);
INSERT INTO `t_ip` VALUES (1055, '192.168.0.3', '加速机1', '百度网盘', 3, 0, '299', 'F：/', 1);
INSERT INTO `t_ip` VALUES (1056, '192.168.0.4', '节点1', '百度网盘', 3, 0, '299', 'F：/', 4);
INSERT INTO `t_ip` VALUES (1057, '192.168.0.5', '节点2', '百度网盘', 3, 0, '299', 'F：/', 4);
INSERT INTO `t_ip` VALUES (1058, '192.168.0.6', '加速机1', '百度网盘', 3, 0, '299', 'F：/', 4);
INSERT INTO `t_ip` VALUES (1059, '192.168.10.1', '节点3', '百度网盘', 3, 0, '299', 'F：/', 2);
INSERT INTO `t_ip` VALUES (1060, '192.168.10.2', '节点4', '百度网盘', 3, 0, '299', 'F：/', 2);
INSERT INTO `t_ip` VALUES (1061, '192.168.10.3', '加速机2', '百度网盘', 3, 0, '299', 'F：/', 2);
INSERT INTO `t_ip` VALUES (1062, '192.168.10.4', '节点3', '百度网盘', 3, 0, '299', 'F：/', 5);
INSERT INTO `t_ip` VALUES (1063, '192.168.10.5', '节点4', '百度网盘', 3, 0, '299', 'F：/', 5);
INSERT INTO `t_ip` VALUES (1064, '192.168.10.6', '加速机2', '百度网盘', 3, 0, '299', 'F：/', 5);
INSERT INTO `t_ip` VALUES (1065, '192.168.100.1', '节点5', '百度网盘', 3, 0, '299', 'F：/', 3);
INSERT INTO `t_ip` VALUES (1066, '192.168.100.2', '节点6', '百度网盘', 3, 0, '299', 'F：/', 3);
INSERT INTO `t_ip` VALUES (1067, '192.168.100.3', '加速机3', '百度网盘', 3, 0, '299', 'F：/', 3);
INSERT INTO `t_ip` VALUES (1068, '192.168.100.4', '节点5', '百度网盘', 3, 0, '299', 'F：/', 6);
INSERT INTO `t_ip` VALUES (1069, '192.168.100.5', '节点6', '百度网盘', 3, 0, '299', 'F：/', 6);
INSERT INTO `t_ip` VALUES (1070, '192.168.100.6', '加速机3', '百度网盘', 3, 0, '299', 'F：/', 6);
INSERT INTO `t_ip` VALUES (1071, '192.168.0.1', '节点1', '百度', 1, 0, '299', 'D：/debug', 1);
INSERT INTO `t_ip` VALUES (1072, '192.168.0.4', '节点1', '百度', 1, 0, '299', 'D：/debug', 4);
INSERT INTO `t_ip` VALUES (1073, '192.168.10.1', '节点3', '百度', 1, 0, '299', 'D：/debug', 2);
INSERT INTO `t_ip` VALUES (1074, '192.168.10.4', '节点3', '百度', 1, 0, '299', 'D：/debug', 5);
INSERT INTO `t_ip` VALUES (1075, '192.168.100.1', '节点5', '百度', 1, 0, '299', 'D：/debug', 3);
INSERT INTO `t_ip` VALUES (1076, '192.168.100.4', '节点5', '百度', 1, 0, '299', 'D：/debug', 6);
INSERT INTO `t_ip` VALUES (1077, '', '', 'A', 1, 0, '68', '11', 0);
INSERT INTO `t_ip` VALUES (1078, '', '', 'A', 1, 0, '68', '11', 0);
INSERT INTO `t_ip` VALUES (1079, '', '', 'A', 1, 0, '68', '11', 0);
INSERT INTO `t_ip` VALUES (1080, '', '', 'A', 1, 0, '68', '11', 0);
INSERT INTO `t_ip` VALUES (1081, '', '', 'A', 1, 0, '68', '11', 0);
INSERT INTO `t_ip` VALUES (1082, '', '', 'A', 1, 0, '68', '11', 0);
INSERT INTO `t_ip` VALUES (1083, '', '', 'EEEE', 1, 0, '68', '111', 0);
INSERT INTO `t_ip` VALUES (1084, '', '', 'EEEE', 1, 0, '68', '111', 0);
INSERT INTO `t_ip` VALUES (1085, '', '', 'EEEE', 1, 0, '68', '111', 0);
INSERT INTO `t_ip` VALUES (1086, '', '', 'EEEE', 1, 0, '68', '111', 0);
INSERT INTO `t_ip` VALUES (1087, '', '', 'EEEE', 1, 0, '68', '111', 0);
INSERT INTO `t_ip` VALUES (1088, '', '', 'EEEE', 1, 0, '68', '111', 0);
INSERT INTO `t_ip` VALUES (1089, '192.168.0.1', '节点1', '夸克', 4, 0, '283', 'C：/', 1);
INSERT INTO `t_ip` VALUES (1090, '192.168.0.2', '节点2', '夸克', 4, 0, '283', 'C：/', 1);
INSERT INTO `t_ip` VALUES (1091, '192.168.0.3', '加速机1', '夸克', 4, 0, '283', 'C：/', 1);
INSERT INTO `t_ip` VALUES (1092, '192.168.0.4', '节点1', '夸克', 4, 0, '283', 'C：/', 4);
INSERT INTO `t_ip` VALUES (1093, '192.168.0.5', '节点2', '夸克', 4, 0, '283', 'C：/', 4);
INSERT INTO `t_ip` VALUES (1094, '192.168.0.6', '加速机1', '夸克', 4, 0, '283', 'C：/', 4);
INSERT INTO `t_ip` VALUES (1095, '192.168.10.1', '节点3', '夸克', 4, 0, '283', 'C：/', 2);
INSERT INTO `t_ip` VALUES (1096, '192.168.10.2', '节点4', '夸克', 4, 0, '283', 'C：/', 2);
INSERT INTO `t_ip` VALUES (1097, '192.168.10.3', '加速机2', '夸克', 4, 0, '283', 'C：/', 2);
INSERT INTO `t_ip` VALUES (1098, '192.168.10.4', '节点3', '夸克', 4, 0, '283', 'C：/', 5);
INSERT INTO `t_ip` VALUES (1099, '192.168.10.5', '节点4', '夸克', 4, 0, '283', 'C：/', 5);
INSERT INTO `t_ip` VALUES (1100, '192.168.10.6', '加速机2', '夸克', 4, 0, '283', 'C：/', 5);
INSERT INTO `t_ip` VALUES (1101, '192.168.100.1', '节点5', '夸克', 4, 0, '283', 'C：/', 3);
INSERT INTO `t_ip` VALUES (1102, '192.168.100.2', '节点6', '夸克', 4, 0, '283', 'C：/', 3);
INSERT INTO `t_ip` VALUES (1103, '192.168.100.3', '加速机3', '夸克', 4, 0, '283', 'C：/', 3);
INSERT INTO `t_ip` VALUES (1104, '192.168.100.4', '节点5', '夸克', 4, 0, '283', 'C：/', 6);
INSERT INTO `t_ip` VALUES (1105, '192.168.100.5', '节点6', '夸克', 4, 0, '283', 'C：/', 6);
INSERT INTO `t_ip` VALUES (1106, '192.168.100.6', '加速机3', '夸克', 4, 0, '283', 'C：/', 6);

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
) ENGINE = InnoDB AUTO_INCREMENT = 33 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_one_click_load
-- ----------------------------
INSERT INTO `t_one_click_load` VALUES (21, 'A', 299, 1);
INSERT INTO `t_one_click_load` VALUES (23, 'C', 299, 3);
INSERT INTO `t_one_click_load` VALUES (26, '111', 283, 1);
INSERT INTO `t_one_click_load` VALUES (27, '3333', 283, 3);
INSERT INTO `t_one_click_load` VALUES (28, '4444', 283, 4);
INSERT INTO `t_one_click_load` VALUES (29, '22', 283, 2);
INSERT INTO `t_one_click_load` VALUES (30, '1', 303, 1);
INSERT INTO `t_one_click_load` VALUES (31, '22', 303, 2);
INSERT INTO `t_one_click_load` VALUES (33, '4444', 303, 4);

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
  `ip` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL COMMENT 'IP地址',
  `number` int NOT NULL,
  `username` varchar(255) CHARACTER SET gb2312 COLLATE gb2312_chinese_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `index_PKID`(`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 221 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_tools
-- ----------------------------
INSERT INTO `t_tools` VALUES (169, 'ps', 'host2', 'd:', 'd:', 2, '', 0, '');
INSERT INTO `t_tools` VALUES (170, 'AE', 'host2', 'D', 'D', 2, '', 0, '');
INSERT INTO `t_tools` VALUES (171, 'PS', 'hots3', 'D', 'E', 3, '', 0, '');
INSERT INTO `t_tools` VALUES (172, 'AR', 'host4', 'E', 'E:', 4, '', 0, '');
INSERT INTO `t_tools` VALUES (173, 'AD', '1', '1', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\adobe_xd.png', 1, '', 0, '');
INSERT INTO `t_tools` VALUES (182, 'DI', 'host1', 'D', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 2, '', 0, '');
INSERT INTO `t_tools` VALUES (183, 'CE', 'host2', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'D', 2, '', 0, '');
INSERT INTO `t_tools` VALUES (185, 'DI', 'host3', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'E', 3, '', 0, '');
INSERT INTO `t_tools` VALUES (186, 'DI', 'host3', 'D:1_projectjqgdemoqtdigitalIntegrationicon.ico', 'E', 3, '', 0, '');
INSERT INTO `t_tools` VALUES (189, 'CD', 'VD', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\icon.ico', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\icon.ico', 2, '', 0, '');
INSERT INTO `t_tools` VALUES (190, 'QQ', 'host1', 'D:\\tools\\QQ\\Bin\\QQ.exe', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\QQ.png', 1, '', 0, '');
INSERT INTO `t_tools` VALUES (191, 'EV录屏', 'host1', 'D:\\tools\\EVCapture\\EVCapture.exe', 'D:\\1_project\\jqg\\demo\\qt\\digitalIntegration\\image\\EV.ico', 1, '', 0, '');
INSERT INTO `t_tools` VALUES (194, '1', 'host2', '1', '1', 2, '', 0, '');
INSERT INTO `t_tools` VALUES (197, 'VS', 'host2', 'VS', 'VS', 1, '', 0, '');
INSERT INTO `t_tools` VALUES (198, 'A1', '节点1', '', '0', 1, '192.168.0.1', 1, '');
INSERT INTO `t_tools` VALUES (199, 'B1', '节点1', '', '0', 1, '192.168.0.1', 1, '');
INSERT INTO `t_tools` VALUES (200, 'D1', '节点2', '', '0', 1, '192.168.0.2', 1, '');
INSERT INTO `t_tools` VALUES (201, 'C1', '加速机1', '', '0', 1, '192.168.0.3', 1, '');
INSERT INTO `t_tools` VALUES (202, 'A2', '节点1', '', '0', 1, '192.168.0.4', 4, '');
INSERT INTO `t_tools` VALUES (203, 'B2', '节点1', '', '0', 1, '192.168.0.4', 4, '');
INSERT INTO `t_tools` VALUES (204, 'D2', '节点2', '', '0', 1, '192.168.0.5', 4, '');
INSERT INTO `t_tools` VALUES (205, 'C2', '加速机1', '', '0', 1, '192.168.0.6', 4, '');
INSERT INTO `t_tools` VALUES (206, 'A3', '节点3', '', '0', 1, '192.168.10.1', 2, '');
INSERT INTO `t_tools` VALUES (207, 'B3', '节点3', '', '0', 1, '192.168.10.1', 2, '');
INSERT INTO `t_tools` VALUES (208, 'D3', '节点4', '', '0', 1, '192.168.10.2', 2, '');
INSERT INTO `t_tools` VALUES (209, 'C3', '加速机2', '', '0', 1, '192.168.10.3', 2, '');
INSERT INTO `t_tools` VALUES (210, 'A4', '节点3', '', '0', 1, '192.168.10.4', 5, '');
INSERT INTO `t_tools` VALUES (211, 'B4', '节点3', '', '0', 1, '192.168.10.4', 5, '');
INSERT INTO `t_tools` VALUES (212, 'D4', '节点4', '', '0', 1, '192.168.10.5', 5, '');
INSERT INTO `t_tools` VALUES (213, 'C4', '加速机2', '', '0', 1, '192.168.10.6', 5, '');
INSERT INTO `t_tools` VALUES (214, 'A5', '节点5', '', '0', 1, '192.168.100.1', 3, '');
INSERT INTO `t_tools` VALUES (215, 'B5', '节点5', '', '0', 1, '192.168.100.1', 3, '');
INSERT INTO `t_tools` VALUES (216, 'D5', '节点6', '', '0', 1, '192.168.100.2', 3, '');
INSERT INTO `t_tools` VALUES (217, 'C5', '加速机3', '', '0', 1, '192.168.100.3', 3, '');
INSERT INTO `t_tools` VALUES (218, 'A6', '节点5', '', '0', 1, '192.168.100.4', 6, '');
INSERT INTO `t_tools` VALUES (219, 'B6', '节点5', '', '0', 1, '192.168.100.4', 6, '');
INSERT INTO `t_tools` VALUES (220, 'D6', '节点6', '', '0', 1, '192.168.100.5', 6, '');
INSERT INTO `t_tools` VALUES (221, 'C6', '加速机3', '', '0', 1, '192.168.100.6', 6, '');

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
) ENGINE = InnoDB AUTO_INCREMENT = 323 CHARACTER SET = gb2312 COLLATE = gb2312_chinese_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of t_user
-- ----------------------------
INSERT INTO `t_user` VALUES (68, '1', '1', '1', '1', '1', '1', '0', '2021-03-04 19:27:50', '1', 0);
INSERT INTO `t_user` VALUES (80, '2', '2', '2', '', '', '', '0', '2024-06-21 09:52:01', '2', 0);
INSERT INTO `t_user` VALUES (81, '2', '2', '2', '', '', '', '0', '2024-06-21 09:54:54', '2', 0);
INSERT INTO `t_user` VALUES (82, '3', '3', '3', '3', '3', '3', '0', '2024-06-21 13:39:07', '1', 0);
INSERT INTO `t_user` VALUES (83, '44', '3', '梁超群', '33', '3', '3', '0', '2024-06-24 10:14:08', '1', 0);
INSERT INTO `t_user` VALUES (84, '21', '21', '21', '21', '21', '21', '0', '2024-06-24 10:41:30', '2', 0);
INSERT INTO `t_user` VALUES (85, '22', '22', '22', '22', '22', '22', '0', '2024-06-24 10:41:39', '1', 0);
INSERT INTO `t_user` VALUES (86, '23', '23', '23', '23', '23', '23', '0', '2024-06-24 10:41:49', '2', 0);
INSERT INTO `t_user` VALUES (87, '31', '31', '31', '31', '', '31', '0', '2024-06-24 11:52:43', '1', 0);
INSERT INTO `t_user` VALUES (88, '32', '32', '32', '32', '32', '32', '0', '2024-06-24 11:52:54', '1', 0);
INSERT INTO `t_user` VALUES (89, '33', '33', '33', '33', '3', '', '0', '2024-06-24 11:53:03', '1', 0);
INSERT INTO `t_user` VALUES (90, '34', '34', '34', '', '', '', '1', '2024-06-24 11:53:18', '1', 0);
INSERT INTO `t_user` VALUES (91, '35', '35', '35', '', '', '', '1', '2024-06-24 11:53:28', '0', 0);
INSERT INTO `t_user` VALUES (92, '41', '41', '41', '41', '41', '41', '1', '2024-06-24 17:31:47', '1', 0);
INSERT INTO `t_user` VALUES (93, '42', '444', '42', '42', '42', '42', '1', '2024-06-24 17:31:59', '0', 0);
INSERT INTO `t_user` VALUES (94, '43', '434', '43', '434', '43', '43', '1', '2024-06-24 17:32:13', '2', 0);
INSERT INTO `t_user` VALUES (95, '45', '444', '44', '44', '44', '44', '1', '2024-06-24 17:32:30', '1', 0);
INSERT INTO `t_user` VALUES (96, '46', '46', '46', '46', '46', '46', '1', '2024-06-24 17:32:48', '0', 0);
INSERT INTO `t_user` VALUES (97, '47', '47', '47', '47', '47', '47', '1', '2024-06-24 17:33:01', '0', 0);
INSERT INTO `t_user` VALUES (98, '48', '48', '48', '48', '48', '48', '0', '2024-06-24 17:33:09', '2', 0);
INSERT INTO `t_user` VALUES (99, '49', '49', '49', '49', '49', '49', '1', '2024-06-24 17:33:21', '1', 0);
INSERT INTO `t_user` VALUES (283, 'wz', '1', '1', '1', '1', '1', '1', '2024-09-04 13:34:06', '1', 1);
INSERT INTO `t_user` VALUES (299, '4', '4', '4', '4', '4', '4', '0', '2024-09-09 10:08:27', '1', 0);
INSERT INTO `t_user` VALUES (319, '5', '5', '5', '5', '5', '5', '0', '2024-09-21 15:03:36', '1', 1);
INSERT INTO `t_user` VALUES (320, '6', '6', '6', '6', '6', '6', '0', '2024-09-21 15:06:00', '1', 0);
INSERT INTO `t_user` VALUES (321, '7', '7', '7', '7', '7', '7', '0', '2024-09-21 15:14:55', '1', 0);
INSERT INTO `t_user` VALUES (322, '8', '8', '8', '8', '8', '8', '0', '2024-09-21 15:20:07', '1', 0);

SET FOREIGN_KEY_CHECKS = 1;
