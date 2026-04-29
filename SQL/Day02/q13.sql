-- 查询客户最大和最小年龄
SELECT MAX(
        DATEDIFF (YEAR, 出生日期, GETDATE ())
    ) AS 最大年龄, MIN(
        DATEDIFF (YEAR, 出生日期, GETDATE ())
    ) AS 最小年龄
FROM dbo.CustomerInfo;