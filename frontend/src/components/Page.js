import React from 'react';
import { ThemeProvider, PageLayout, BaseStyles, Header, StyledOcticon, Breadcrumbs } from '@primer/react';
import { DesktopDownloadIcon, WorkflowIcon, GearIcon, CpuIcon } from '@primer/octicons-react';

export function PHeader (props) {
  return <Header>

  <Header.Item>
    <Header.Link href="/" fontSize={2}>
      <StyledOcticon icon={DesktopDownloadIcon} sx={{ mr: 2 }} />
      <span>Thing Downloader</span>
    </Header.Link>
  </Header.Item>

  <Header.Item full/>

  <Header.Item>
    <Header.Link href="/jobs" sx={{ fontWeight: 'normal' }}>
      <StyledOcticon icon={WorkflowIcon} sx={{ mr: 2 }} />
      <span>Jobs</span>
    </Header.Link>
  </Header.Item>

  <Header.Item>
    <Header.Link href="/settings" sx={{ fontWeight: 'normal' }}>
      <StyledOcticon icon={CpuIcon} sx={{ mr: 2 }} />
      <span>Plugins</span>
    </Header.Link>
  </Header.Item>

  <Header.Item>
    <Header.Link href="/settings" sx={{ fontWeight: 'normal' }}>
      <StyledOcticon icon={GearIcon} sx={{ mr: 2 }} />
      <span>Options</span>
    </Header.Link>
  </Header.Item>

</Header>;
}

export default function Page (props) {
  return (<ThemeProvider>
    <BaseStyles>
    <PHeader/>
    <PageLayout>
        <PageLayout.Content>
        <Breadcrumbs>
{
props.bc
  ? props.bc.map(
    (rank, i, row) =>
    <Breadcrumbs.Item key={rank[0]} selected={(i + 1 === row.length)} href={rank[0]}>{rank[1]}</Breadcrumbs.Item>
  )
  : <></>
}

</Breadcrumbs>

      {props.children}
 </PageLayout.Content>
 </PageLayout>
 </BaseStyles>
 </ThemeProvider>);
}
