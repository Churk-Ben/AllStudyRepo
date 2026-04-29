-- 按性别统计江苏的客户数量
SELECT 性别, COUNT(*) AS 客户数量
FROM dbo.CustomerInfo
WHERE
    所在省市 LIKE '江苏%'
GROUP BY
    性别;