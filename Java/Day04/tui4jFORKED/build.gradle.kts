// build.gradle.kts
import java.io.FileInputStream
import java.io.FileOutputStream
plugins {
    // 启用 Java 应用程序支持
    application
}

repositories {
    // 声明使用标准中央仓库
    mavenCentral()
}

dependencies {
    // 引入 tui4j 依赖
    implementation("com.williamcallahan:tui4j:0.3.3")
    runtimeOnly("org.jline:jline-terminal-jansi:3.26.1")
    runtimeOnly("org.jline:jline-terminal-jna:3.26.1")
}

java {
    toolchain {
        languageVersion.set(JavaLanguageVersion.of(21))
    }
}

application {
    // 指定程序的主入口类（第三步我们会创建这个类）
    mainClass.set("examples.showcases.PulseExample")
    applicationDefaultJvmArgs = listOf(
        "-Dorg.jline.terminal.dumb=true"
    )
}

tasks.named<JavaExec>("run") {
    standardInput = System.`in`
    standardOutput = System.out
    errorOutput = System.err
    doFirst {
        if (org.gradle.internal.os.OperatingSystem.current().isWindows) {
            runCatching {
                standardInput = FileInputStream("CONIN$")
                val conOut = FileOutputStream("CONOUT$")
                standardOutput = conOut
                errorOutput = conOut
            }
        }
    }
}
