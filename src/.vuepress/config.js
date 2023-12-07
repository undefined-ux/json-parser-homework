const { description } = require('../../package')
// import { hopeTheme } from "vuepress-theme-hope";
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
    author: "undefined-ux",
    editLinks: false,
    docsDir: '',
    editLinkText: '',
    lastUpdated: "最近更新于", 
    subSidebar: 'auto',
    sidebar: [
      {
        title: '命令行',   // required
        path: '/cli/',      // optional, link of the title, which should be an absolute path and must exist
        sidebarDepth: 2,    // optional, defaults to 1
        children: [
          {title: "总览", path: '/cli/'},
          {title: "指定输入/输出流", path: '/cli/io'},
          {title: "输出格式化选项", path: '/cli/output'},
          {title: "其它", path: '/cli/other'}
        ]
      },
      {
        title: '解析库',   // required
        path: '/core/',      // optional, link of the title, which should be an absolute path and must exist
        sidebarDepth: 3,    // optional, defaults to 1
        children: [
          {title: "总览", path: '/core/'},
          {title: "类型", path: '/core/types'},
          {title: "输出", path: '/core/output'},
          {title: "解析", path: '/core/parser'}
        ]
      }
    ],
    footer: {
      message: 'MIT Licensed | Rendered by VitePress',
      copyright: 'Copyright © 2023-2024 undefined'
    }
  },
  theme: 'reco',
  // theme: hopeTheme({
  //   darkmode: 'auto',
  //   plugins: {
  //     copyCode: {
  //       showInMobile: true
  //     },
  //   },
  // }),

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
