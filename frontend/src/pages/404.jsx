import * as React from 'react';
import Page from '../components/Page';
import { Link, Heading, Text } from '@primer/react';

const NotFoundPage = (props) => {
  return (
    <Page bc={[['/', 'Thing Downloader'], [props.location.pathname, 'Not Found']]}>
      <Heading>Page Not Found</Heading>
      <Text as="p">The Page you are looking for cannot be found.</Text>
      <Text as="p">You should probably <Link href="/">return to the home page</Link> or press back in your browser.</Text>
    </Page >
  );
};

export default NotFoundPage;

export const Head = () => <title>404 - Not found</title>;
