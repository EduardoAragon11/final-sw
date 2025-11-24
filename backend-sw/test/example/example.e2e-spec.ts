import { Test, TestingModule } from '@nestjs/testing';
import { INestApplication } from '@nestjs/common';
import request from 'supertest';
import { AppModule } from '../../src/app.module';

describe('Example E2E', () => {
  let app: INestApplication;
  let token: string;

  beforeAll(async () => {
    const moduleFixture: TestingModule = await Test.createTestingModule({
      imports: [AppModule],
    }).compile();

    app = moduleFixture.createNestApplication();
    await app.init();

    // login to get token
    const res = await request(app.getHttpServer())
      .post('/auth/login')
      .send({ username: 'admin', password: 'adminpass' });

    token = res.body.access_token;
  });

  afterAll(async () => {
    await app.close();
  });

  it('/example/public (GET)', async () => {
    const res = await request(app.getHttpServer())
      .get('/example/public')
      .expect(200);

    expect(res.body.message).toBe('This is a public endpoint');
  });

  it('/example/protected (GET)', async () => {
    const res = await request(app.getHttpServer())
      .get('/example/protected')
      .set('Authorization', `Bearer ${token}`)
      .expect(200);

    expect(res.body.message).toContain('you are authenticated');
  });

  it('/example/admin (GET) requires Admin role', async () => {
    await request(app.getHttpServer())
      .get('/example/admin')
      .set('Authorization', `Bearer ${token}`)
      .expect(200);
  });
});
