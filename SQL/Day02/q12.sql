-- 查询每个客户的年龄
SELECT 客户编号, 客户姓名, DATEDIFF (YEAR, 出生日期, GETDATE ()) AS 年龄
FROM dbo.CustomerInfo;