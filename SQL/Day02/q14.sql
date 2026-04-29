-- 查询客户的平均年龄
SELECT AVG(
        DATEDIFF (YEAR, 出生日期, GETDATE ())
    ) AS 平均年龄
FROM dbo.CustomerInfo;