import React from 'react';
import { Header } from '@primer/react';

export default function PageHeader (props) {
  return (<Header>

    <Header.Item full>
    <Header.Link href="/">
      <span>Thing Downloader</span>
      </Header.Link>
    </Header.Item>

    <Header.Item>
    <Header.Link href="/">
      Download Queue
    </Header.Link>
    </Header.Item>

    <Header.Item>
    <Header.Link href="/">
      Plugins
    </Header.Link>
    </Header.Item>

    <Header.Item>
    <Header.Link href="/">
      Options
    </Header.Link>
    </Header.Item>
</Header>);
}
