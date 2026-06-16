<%--page指令标签，指定MIME类型和页面的字符编码--%>
    <%@ page contentType="text/html; charset=gb2312" %>
        <%--声明一个类方法，该方法在整个JSP页面有效--%>
            <%! int continuousSum(int n) { int sum=0; for (int i=1; i <=n; i++) { sum=sum + i; } return sum; } %>
                <%--JSP中的Java程序片，将被JSP引擎按顺序执行--%>
                    <% String str=request.getParameter("number"); if (str==null) { str="10" ; } int
                        r=Integer.parseInt(str); %>
                        <html>

                        <head>
                            <title>计算连续和</title>
                        </head>

                        <body>
                            <h1>请输人一个自然数</h1>
                            <!--HTML表单-->
                            <form name="forml" method="post" action="">
                                <input type="text" name="number" value=<%=str%>>
                                <input type="submit" name="Submit" value="计算">
                            </form>
                            <%-- JSP表达式，其值由服务器负责计算，并将结果发回客户端显示--%>
                                <%=r%>的连续和是<%=continuousSum(r)%>
                        </body>

                        </html>