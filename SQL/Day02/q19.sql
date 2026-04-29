-- 统计各地的客户数量
SELECT 所在省市, COUNT(*) AS 客户数量 FROM dbo.CustomerInfo GROUP BY 所在省市;