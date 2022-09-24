import * as React from 'react';
import LinkCountBar from '../components/LinkCountBar';
import ReactMarkdown from 'react-markdown';
import Page from '../components/Page';

import { Heading } from '@primer/react';
import Content from '../../../Readme.md';

const IndexPage = () => {
  // break the textblock into an array of lines
  const lines = Content.split('\n');
  // remove one line, starting at the first position
  lines.splice(0, 1);
  // join the array back into a single string
  const newtext = lines.join('\n');

  return (
    <Page bc={[]}>
      <Heading>Thing Downloader</Heading>
      <LinkCountBar />

      <ReactMarkdown>
        {newtext}
      </ReactMarkdown>
    </Page>

  );
};

export default IndexPage;

export const Head = () => <title>Thing Downloader</title>;
