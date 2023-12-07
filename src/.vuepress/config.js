const { description } = require('../../package')

module.exports = {
  /**
   * Ref：https://v1.vuepress.vuejs.org/config/#title
   */
  title: '文档',
  /**
   * Ref：https://v1.vuepress.vuejs.org/config/#description
   */
  description: "",

  /**
   * Extra tags to be injected to the page HTML `<head>`
   *
   * ref：https://v1.vuepress.vuejs.org/config/#head
   */
  head: [
    ['meta', { name: 'theme-color', content: '#3eaf7c' }],
    ['meta', { name: 'apple-mobile-web-app-capable', content: 'yes' }],
    ['meta', { name: 'apple-mobile-web-app-status-bar-style', content: 'black' }]
  ],

  /**
   * Theme configuration, here is the default theme configuration for VuePress.
   *
   * ref：https://v1.vuepress.vuejs.org/theme/default-theme-config.html
   */
  themeConfig: {
    repo: 'undefined-ux/json-parser-homework',
    editLinks: false,
    docsDir: '.',
    editLinkText: '',
    lastUpdated: "最近更新于",
    sidebar: [
      ['/cli', '命令行'],
      ['/cli/','总览'],
      ['/cli/io', '指定输入/输出'],
      ['/cli/output', '指定输出格式'],
      ['/cli/other', '其它'],
      ['/core/', '解析库'],
    ],
    footer: {
      message: 'MIT Licensed | Rendered by VitePress',
      copyright: 'Copyright © 2023-2024 undefined'
    }
  },

  /**
   * Apply plugins，ref：https://v1.vuepress.vuejs.org/zh/plugin/
   */
  plugins: [
    '@vuepress/plugin-back-to-top',
    '@vuepress/plugin-medium-zoom',
  ],
  markdown: {
    lineNumbers: true
  }
}
