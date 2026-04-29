-- 查询客户最早和最晚出生日期
SELECT MIN(出生日期) AS 最早出生日期, MAX(出生日期) AS 最晚出生日期
FROM dbo.CustomerInfo;